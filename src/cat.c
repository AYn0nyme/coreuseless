#include "include/utils.h"
#include <stdio.h>

#define MAX_LINE_LENGTH 8192

const char* usage = "cat [FILE...]\nget the content of a/some file.s";

struct option options[] = {
};

int cat(const char* path) {
  FILE* file = fopen(path, "r");
  if(file == NULL) {
    printf("cat: file %s does not exist\n", path);
    return 1;
  }
  char c;
  while((c = fgetc(file)) != EOF) {
    putchar(c);
  }
  fclose(file);
  return 0;
}

int main(int argc, char** argv) {
  parse_args(argc, argv, options, array_len(options));

  for(int c = 1; c < argc; c++) {
    if(argv[c][0]=='-')continue;
    if(cat(argv[c])) return 1;
    if(c < argc-1)puts("---");
  }
}
