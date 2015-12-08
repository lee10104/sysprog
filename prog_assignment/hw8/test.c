//------------------------------------------------------------------------------
// M1522.000800               System Programming                      Fall 2015
//
// Homework Assignment 8
//
// Intercept calls to fopen/fclose by using library interpositioning
//
// File: test.c
//
// (C) 2015 Computer Systems and Platforms Laboratory, Seoul National University
//
// Changelog
// 20151104   hochan      created
// 20151105   bernhard    clean-up
//

#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input"
#define BUFFER_MAX 1024

int main(void)
{
  FILE *fp = NULL;
  char buff[BUFFER_MAX];

  if ((fp = fopen(INPUT_FILE, "r")) == NULL) {
    perror("Cannot open input file");
    return EXIT_FAILURE;
  }

  printf("Contents of '%s': ", INPUT_FILE);
  while (fgets(buff, BUFFER_MAX, fp)) {
    printf("%s", buff);
  }

  if (fclose(fp) != 0) {
    perror("Cannot close file");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
