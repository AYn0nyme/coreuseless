#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

const char* usage = "sleep [SECONDS]\nsleep for SECONDS seconds";

int main(int argc, char** argv) {
  if(argc < 2) {
    puts("sleep: need an argument");
    return 1;
  }
  long sec = strtol(argv[1], NULL, 0);
  errno = 0;
  if(errno == EINVAL) {
    perror("sleep");
    return 1;
  }
  sleep(sec);
}
