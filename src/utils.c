#include "include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char* usage;

const char* version = "FROST Coreuseless version 1.0\nhttps://github.com/AYn0nyme/coreuseless - Report issues: https://github.com/AYn0nyme/coreuseless/issues";

struct parsed parse_args(int argc, char **argv, struct option options[], size_t options_count){
  struct parsed output;
  for(int c = 1; c < argc; c++) {
    if(argv[c][0] != '-') continue;
    if(argv[c][1] == '-') {
      if(!strcmp(argv[c], "--help")) {
        puts(usage);
        for(size_t i = 0; i < options_count; i++) {
          printf("-%c, --%s  %s", options[i].small, options[i].name, options[i].description);
          putchar('\n');
        }
        exit(0);
      } else if (!strcmp(argv[c], "--version")) {
        puts(version);
        exit(0);
      }
      for(size_t i = 0; i < options_count; i++) {
        if(!strcmp(strtok(argv[c], "--"), options[i].name)) {
          output.flags |= options[i].flag;
          if(options[i].takes_value) {
            for(size_t j = 0; j < strlen(argv[c]); j++){
              
            }
          }
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
            output.flags |= options[i].flag;
            break;
          }
        }
      }
      
    }
  }
  return output;
}
