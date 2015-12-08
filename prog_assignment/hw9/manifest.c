//------------------------------------------------------------------------------
// M1522.000800               System Programming                      Fall 2015
//
// Homework Assignment 9
//
// Create a manifest file containing md5sums of a directory
//
// File: manifest.c
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

  // TODO
  //
  // 1. create manifest file MANIFEST_FILE with the permissions -rw-r--r--
  // 2. open directory specified on command line
  //

  // TODO
  //
  // iterate through each entry in directory and compute the md5sum for each 
  // regular file (except MANIFEST_FILE). To compute the md5sum, you need to 
  // fork off a child md5sum process using fork()/execvp()
  //
  // TODO in child
  //
  // 1. change directory into directory specified on the command line
  // 2. redirect stdout to output (manifest) file
  // 3. prepare command line arguments for md5sum
  // 4. execute md5sum
  //
  // TODO in parent
  //
  // 1. wait for child
  // 2. check return status, printing error if necessary
  //

  // TODO
  //
  // close directory and manifest file, then exit



  fprintf(stdout, "%s created.\n", MANIFEST_FILE);

  return EXIT_SUCCESS;
}
