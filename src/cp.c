#include "../include/utils.h"
#include <stdio.h>

#define FLAG_FORCE (1 << 2)

const char* usage = "cp [SOURCE] [DESTINATION]\ncopy the content of SOURCE to DESTINATION";

struct option options[] = {
  opt("force",'f',FLAG_FORCE,"force create file if exists"),
};

void cp(const char* from, const char* to, int flags) {
  FILE* file = fopen(from, "r");
  if (file == NULL) {
    printf("cp : file %s not found\n", from);
    return;
  }
  FILE* new_file = fopen(to, "r");
  if(new_file != NULL && !(flags & FLAG_FORCE)) {
    printf("cp : file %s already exists\n", to);
    return;
  }
  new_file = fopen(to, "w");
  fprintf(new_file, "");
  char c;
  while((c = fgetc(file)) != EOF) {
    fputc(c, new_file);
  }

  fclose(file);
  fclose(new_file);
}

int main(int argc, char** argv) {
  int flags = parse_args(argc, argv, options, array_len(options));

  char* from;
  char* to;
  
  int count = 0;
  for(int c = 1; c < argc; c++) {
    if(argv[c][0] == '-') continue;
    if(count == 0) {
      from = argv[c];
    } else if (count == 1) {
      to = argv[c];
    }
    count++;
  }
  if (count == 0) {
    puts("cp : missing arguments");
    return 1;
  }
  cp(from, to, flags);
}
