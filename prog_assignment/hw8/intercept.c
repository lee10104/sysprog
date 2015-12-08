//------------------------------------------------------------------------------
// M1522.000800               System Programming                      Fall 2015
//
// Homework Assignment 8
//
// Intercept calls to fopen/fclose by using library interpositioning
//
// File: sp_foc.c
//
// (C) 2015 Computer Systems and Platforms Laboratory, Seoul National University
//
// Changelog
// 20151104   hochan      created
// 20151105   bernhard    clean-up
//
// Name:       Eunha Lee
// Student-ID: 2013-11422
//

#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>
#include <errno.h>

FILE *fopen(const char *path, const char *mode)
{
  // TODO
  //
  // 1) use dlsym() to retrieve the original fopen function
  // 2) print information about opened file (path, mode)
  // 3) call original function and return result

  FILE *fp;

  static FILE *(*sp_fopen)(const char *, const char *) = NULL;

  if (sp_fopen == 0)
    sp_fopen = dlsym(RTLD_NEXT, "fopen");

  printf(">>> intercept: fopen(\"%s\", \"%s\") <<<\n", path, mode);

  fp = sp_fopen(path, mode);

  return fp;
}

int fclose(FILE *stream)
{
  // TODO
  //
  // 1) use dlsym() to retrieve the original fopen function
  // 2) print that a file has been closed
  // 3) call original function and return result

  static int (*sp_fclose)(FILE *) = NULL;

  if (!sp_fclose)
    sp_fclose = dlsym(RTLD_NEXT, "fclose");

  printf(">>> intercept: fclose() <<<\n");

  return sp_fclose(stream);
}
