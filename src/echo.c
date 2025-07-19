#include "../include/utils.h"
#include <string.h>
#include <stdio.h>

#define FLAG_NONWLN (1 << 0)
#define FLAG_NOSPACE (1 << 1)

const char* usage = "echo [TEXT]\nechoes TEXT\n-n, --nonewline    remove the new line\n-s, --nospace    remove the space between arguments";

struct option options[] = {
  opt("nonewline",'n',FLAG_NONWLN,""),
  opt("nospace",'s',FLAG_NOSPACE,""),
};

int main(int argc, char** argv) {
  int flags = parse_args(argc, argv, options, array_len(options));

  for(int c = 0; c < argc; c++) {
    if(!strcmp(argv[c], "-n") || !strcmp(argv[c], "--nonewline") || !strcmp(argv[c], "-s") || !strcmp(argv[c], "--nospace")) continue;
    printf("%s", argv[c]);
    if(!(flags & FLAG_NOSPACE) && c < argc) putchar(' ');
  }
  if(!(flags & FLAG_NONWLN)) putchar('\n');
}
