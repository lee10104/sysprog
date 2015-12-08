//------------------------------------------------------------------------------
// M1522.000800               System Programming                      Fall 2015
//
// Homework Assignment 9
//
// Create a manifest file containing md5sums of a directory
//
// File: manifest.solution.c
//
// (C) 2015 Computer Systems and Platforms Laboratory, Seoul National University
//
// Changelog
// 20151111   bernhard    created
//

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#define MANIFEST_FILE "manifest.txt"

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Missing argument.\n\n"
                    "computes a manifest for a given directory.\n"
                    "Syntax: %s <directory>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  //
  // 1. create manifest file MANIFEST_FILE with the permissions -rw-r--r--
  // 2. open directory specified on command line
  //
  int out = open(MANIFEST_FILE, O_WRONLY|O_CREAT|O_TRUNC, 
                 S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  if (out == -1) {
    perror("Cannot open manifest");
    exit(EXIT_FAILURE);
  }

  DIR *dir = opendir(argv[1]);
  if (dir == NULL) {
    fprintf(stderr, "Cannot open directory '%s': ", argv[1]);
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  //
  // iterate through each entry in directory and compute the md5sum for each 
  // regular file (except MANIFEST_FILE). To compute the md5sum, you need to 
  // fork off a child md5sum process using fork()/execvp()
  //
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    // ignore files that are not regular files and the manifest itself
    if (((entry->d_type & DT_REG) != DT_REG) ||
        (strcmp(entry->d_name, MANIFEST_FILE) == 0)) {
      continue;
    }

    pid_t pid = fork();
    if (pid == 0) {
      //      
      // child
      //
      // 1. change directory into directory specified on the command line
      // 2. redirect stdout to output (manifest) file
      // 3. prepare command line arguments for md5sum
      // 4. execute md5sum
      //
      if (chdir(argv[1]) == -1) {
        perror("Cannot change directory");
        exit(EXIT_FAILURE);
      }

      if (dup2(out, STDOUT_FILENO) != STDOUT_FILENO) {
        perror("Cannot duplicated manifest fd");
        exit(EXIT_FAILURE);
      }

      char *args[3];
      args[0] = strdup("md5sum");
      args[1] = strdup(entry->d_name);
      args[2] = NULL;

      execvp(args[0], args);

      // we only end up here if the execvp call failed
      perror("Cannot execute md5sum process");
      exit(EXIT_FAILURE);
    } else {
      //
      // parent
      //
      // 1. wait for child
      // 2. check return status, printing error if necessary
      //
      int status;
      if (waitpid(pid, &status, 0) == -1) {
        perror("Cannot wait for child process");
      } else {
        if (!WIFEXITED(status) || (WEXITSTATUS(status) != 0)) {
          fprintf(stderr, "Child did not exit normally.\n");
        }
      }
    }
  }

  //
  // close directory and manifest file, then exit
  //
  if (closedir(dir) == -1) perror("Cannot close directory");
  if (close(out) == -1) perror("Cannot close manifest file");

  fprintf(stdout, "%s created.\n", MANIFEST_FILE);

  return EXIT_SUCCESS;
}
