#include "include/utils.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define FLAG_FORCE (1 << 0)
#define FLAG_VERBOSE (1 << 1)

const char* usage = "mv [SOURCE] [DESTINATION]\nmove SOURCE to DESTINATION";



int mv(char* from, const char* to, int flags) {
  FILE* file_from = fopen(from, "r");

  if(file_from == NULL) {
    printf("mv: file %s does not exists\n", from);
    return 1;
  }
  DIR* dir = opendir(to);
  if(dir != NULL) {
    char* dest = strdup(to);
    strcat(dest, "/");
    char* filename;
    char* tmp = strdup(from);
    while((filename = strtok_r(tmp, "/", &tmp))){
      if(strlen(tmp) == 0)break;
    }
    strcat(dest, filename);
    puts(dest);
    return mv(from, dest, flags);
  }
  FILE* file_to = fopen(to, "r");

  if(file_to != NULL && !(flags & FLAG_FORCE)) {
    printf("mv: file %s already exists\n", to);
    return 1;
  }

  file_to = fopen(to, "w");

  char c;
  while ((c = fgetc(file_from)) != EOF) {
    fputc(c, file_to);
  }

  if(flags & FLAG_VERBOSE) printf("mv: moved file %s to %s\n", from, to);

  fclose(file_to);
  fclose(file_from);

  return remove(from);
}

int main(int argc, char** argv) {
  struct option options[] = {
    opt("force",'f',FLAG_FORCE,"force move file"),
    opt("verbose",'i',FLAG_VERBOSE,"get more infos"),
  };

  struct parsed flags = parse_args(argc, argv, options, array_len(options));

  char* from; char* to;
  for(int c = 1; c < argc; c++) {
    if(argv[c][0]=='-')continue;
    if(from == NULL){
      from = argv[c];
    } else {
      to = argv[c];
      break;
    }
  }

  if(from == NULL || to == NULL) {
    puts("mv: need SOURCE and DESTINATION args");
    return 1;
  }

  return mv(from, to, flags.flags);
}
