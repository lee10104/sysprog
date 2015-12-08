/*
 * proxy.c - M1522.000800 System Programming: Web proxy
 *
 * Student ID:   2013-11422
 *         Name: Lee Eunha
 * 
 * IMPORTANT: Give a high level description of your code here. You
 * must also provide a header comment at the beginning of each
 * function that describes what that function does.
 */ 

#include "csapp.h"

/* The name of the proxy's log file */
#define PROXY_LOG "proxy.log"

/* Undefine this if you don't want debugging output */
#define DEBUG

/*
 * Functions to define
 */
void *process_request(void* vargp);
int open_clientfd_ts(char *hostname, int port, sem_t *mutexp);
ssize_t Rio_readn_w(int fd, void *ptr, size_t nbytes);
ssize_t Rio_readlineb_w(rio_t *rp, void *usrbuf, size_t maxlen);
void Rio_writen_w(int fd, void *usrbuf, size_t n);

static FILE *flog;

/*
 * main - Main routine for the proxy program
 */
int main(int argc, char **argv)
{
  int listenfd, connfd, port;
  socklen_t clientlen = sizeof(struct sockaddr_in);
  struct sockaddr_in clientaddr;

  /* Ignore SIGPIPE */
  signal(SIGPIPE, SIG_IGN);

  /* Check arguments */
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
    exit(0);
  }

  port = atoi(argv[1]);

  flog = Fopen(PROXY_LOG, "a");
  listenfd = Open_listenfd(port);

  while (1)
  {
    connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
  }

  exit(0);
}


