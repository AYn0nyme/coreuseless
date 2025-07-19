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

// option_array* parse_args(int argc, char **argv, const char* usage){
//   option_array* return_options = malloc(sizeof(option_array));
//   return_options->size = argc;
//   return_options->array = calloc(argc, sizeof(option));
//   for(int c = 0; c < argc; c++) {
//     if(!strcmp(argv[c], "--help")) {
//       puts(usage);
//       exit(0);
//     } else {
//       if(sizeof(argv[c]) == sizeof(char)) {
//         return_options->array[c].small = (char)argv[c];
//       }
//       return_options->array[c].name = argv[c];
//     }
//   }
//   return return_options;
// }
//
// option_array* create_options(int options_count, option options_[]) {
//   option_array* options = malloc(sizeof(option_array));
//   options->array = calloc(options_count, sizeof(option));
//   options->size = options_count;
//
//   for(int c = 0; c < options_count; c++) {
//     options->array[c] = options_[c];
//   }
//
//   return options;
// }
