#include "include/utils.h"
#include <stdio.h>
#include <unistd.h>

#define FLAG_SYMBOLIC (1 << 0)
#define FLAG_FORCE (1 << 1)
#define FLAG_VERBOSE (1 << 2)

const char* usage = "ln [SOURCE] [DESTINATION]\nlink DESTINATION to SOURCE";

int ln(const char* from, const char* to, int flags) {
  FILE* file_from = fopen(from, "r");

  if(file_from == NULL) {
    printf("ln: file %s does not exist\n", from);
    return 1;
  }

  FILE* file_to = fopen(to, "r");
  if(file_to != NULL && !(flags & FLAG_FORCE)) {
    printf("ln: file %s already exists\n", to);
    return 1;
  }

  if(!(flags & FLAG_SYMBOLIC)) link(from, to);
  else symlink(from, to);

  printf("ln: linked %s to %s\n", to, from);

  return 0;
}

int main(int argc, char** argv) {
  struct option options[] = {
    opt("symbolic",'s',FLAG_SYMBOLIC,"symbolically link files"),
    opt("force",'f',FLAG_FORCE,"force link file"),
    opt("verbose",'i',FLAG_VERBOSE,"get more information"),
  };
  struct parsed flags = parse_args(argc, argv, options, array_len(options));

  char* from = NULL; char* to = NULL;
  if(argc < 3) {
    puts("ln: need 2 arguments");
    return 1;
  }
  for(int c = 1; c < argc; c++) {
    if(argv[c][0]=='-')continue;
    if(from == NULL) {
      from = argv[c];
    } else {
      to = argv[c];
      break;
    }
  }
  if(from == NULL || to == NULL) {
    puts("ln: need 2 arguments");
    return 1;
  }

  return ln(from, to, flags.flags);
}
