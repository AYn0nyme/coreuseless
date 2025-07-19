#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char* usage;

const char* version = "FROST Coreuseless version 1.0\nhttps://github.com/AYn0nyme/coreuseless - Report issues: https://github.com/AYn0nyme/coreuseless#issues";

int parse_args(int argc, char **argv, struct option options[], size_t options_count){
  int flags;
  for(int c = 1; c < argc; c++) {
    if(argv[c][0] != '-') continue;
    if(argv[c][1] == '-') {
      if(!strcmp(argv[c], "--help")) {
        puts(usage);
        exit(0);
      } else if (!strcmp(argv[c], "--version")) {
        puts(version);
        exit(0);
      }
      for(size_t i = 0; i < options_count; i++) {
        if(!strcmp(strtok(argv[c], "--"), options[i].name)) {
          flags |= options[i].flag;
          break;
        }
      }
    } else {
      if(argv[c][1] == 'h') {
        puts(usage);
        exit(0);
      } else if (argv[c][1] == 'v') {
        puts(version);
        exit(0);
      }
      for(size_t j = 1; j < strlen(argv[c]); j++) {
        for(size_t i = 0; i < options_count; i++) {
          if(argv[c][j] == options[i].small) {
            flags |= options[i].flag;
            break;
          }
        }
      }
      
    }
  }
  return flags;
}
