#include "include/utils.h"
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

  struct parsed flags = parse_args(argc, argv, options, array_len(options));

  for(int c = 1; c < argc; c++) {
    if(!strcmp(argv[c], "-n") || !strcmp(argv[c], "--nonewline") || !strcmp(argv[c], "-s") || !strcmp(argv[c], "--nospace") || !strcmp(argv[c], "-ns") || !strcmp(argv[c], "-sn")) continue;
    printf("%s", argv[c]);
    if(!(flags.flags & FLAG_NOSPACE) && c+1 < argc) putchar(' ');
  }
  if(!(flags.flags & FLAG_NONWLN)) putchar('\n');
}
