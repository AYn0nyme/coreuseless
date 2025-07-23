#include "include/utils.h"
#include "types.h"
#include <stdint.h>

#define FLAG_BYTES (1 << 0)
#define FLAG_LINES (1 << 1)

const char* usage = "head [FILE...]\nget the 10 first lines of each FILE";

int head(const char* filepath, int flags) {

  return 0;
}

int main(int argc, char** argv) {
  struct option options[] = {
    optv("bytes",'b',FLAG_BYTES,"get N bytes",(void*)(intptr_t)10,TYPE_INT),
    optv("lines",'n',FLAG_LINES,"get N lines",(void*)(intptr_t)10,TYPE_INT),
  };
  struct parsed flags = parse_args(argc, argv, options, array_len(options));
  for(int c = 1; c < argc; c++) {
    if(argv[c][0]=='-')continue;
    if(head(argv[c], flags.flags)) return 1;
  }
}
