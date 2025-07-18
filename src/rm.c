#include "../include/utils.h"

const char* usage = "rm [FILES...]\nremove all FILES";

struct option options[] = {};

void rm(const char* path) {

}

int main(int argc, char** argv){
  parse_args(argc, argv, options, array_len(options));


  for(int c = 1; c < argc; c++) {
    if(argv[c][0] == '-')continue;
    rm(argv[c]);
  }
}
