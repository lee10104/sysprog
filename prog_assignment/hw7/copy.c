//------------------------------------------------------------------------------
// M1522.000800               System Programming                      Fall 2015
//
// Homework Assignment 7
//
// Copying files using a user buffer and mmap.
//
// Name:       Firstname Lastname
// Student-ID: XXXX-XXXXX
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define M_BUFFER 1
#define M_MMAP   2

int copy_buffer(int in, int out)
{
  // TODO
  //
  // copy the contents of the input file to output using repeated calls
  // to the read/write system calls.
  // Look at read and write's man page (both system calls are outlined
  // in section 2, i.e., use '$ man -S2 read' and '$ man -S2 write' to
  // access the correct man page) to find out how to use them.
  // There is no explicit end-of-file (eof) system call; the man page
  // on read describes how the end of a file can be detected.
  //
  // Tip: vary the size of the copy buffer and check what effect it has
  // on the copying speed.
  //
  // Do not forget error checking. In case of an error, print a message
  // to stderr using fprintf (as done below in main) and return 
  // EXIT_FAILURE


  return EXIT_SUCCESS;
}


int copy_mmap(int in, int out)
{
  // TODO
  //
  // use 'mmap' to map the input file into the process' address space.
  // The call will result in a pointer which can then be given to the
  // 'write' system call to write the buffer to the output file.
  // To retrieve the source file's length, you need to use the 'fstat' 
  // system call and then look at the st_size field.
  //
  // Do not forget error checking. In case of an error, print a message
  // to stderr using fprintf (as done below in main) and return 
  // EXIT_FAILURE


  return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
  int in, out, mode, res = EXIT_FAILURE;

  // make sure the user provided the necessary command line arguments
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <source> <dest> <mode>\n"
                    "\n"
                    "Copies a file from <source> to <dest>.\n"
                    "<mode> must be either 1 or 2 where\n"
                    "  mode==%d      use buffer copy algorithm\n"
                    "  mode==%d      use mmap copy algorithm\n",
                    argv[0], M_BUFFER, M_MMAP);
    exit(EXIT_FAILURE);
  }

  // first check the mode
  mode = atoi(argv[3]);
  if (!((mode == M_BUFFER) || (mode == M_MMAP))) {
    fprintf(stderr, "Invalid copy mode specified (%d)\n", mode);
    exit(EXIT_FAILURE);
  }


  // open the source file read-only and check for errors
  in = open(argv[1], O_RDONLY);
  if (in == -1) {
    perror("Error opening input file");
    exit(EXIT_FAILURE);
  }

  // check if output file exists and abort if yes
  if (access(argv[2], F_OK) == 0) {
    fprintf(stderr, "Cowardly refusing to overwrite an exiting file\n");
    exit(EXIT_FAILURE);
  }

  // open the destination file write-only and check for errors
  out = open(argv[2], O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  if (out == -1) {
    perror("Error opening output file");
    exit(EXIT_FAILURE);
  }

  // invoke file copy
  switch (mode) {
    case M_BUFFER: res = copy_buffer(in, out);
                   break;
    case M_MMAP:   res = copy_mmap(in, out);
                   break;
  }

  // close source & destination
  close(in);
  close(out);

  return res;
}
