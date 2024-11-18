#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void error(const char *msg) {
  if (errno) {
    perror(msg);
  } else {
    fprintf(stderr, "%s\n", msg);
  }
  exit(1);
}
