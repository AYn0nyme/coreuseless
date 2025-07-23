#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <stddef.h>

struct parsed parse_args(int argc, char** argv, struct option options[], size_t options_count);

#define array_len(array) (sizeof(array) / sizeof(*array))
// #define opt(n,c,f,d) {.name = n,.small = c,.flag = f,.description = d,.value=NULL,.takes_value=FALSE}
// #define optv(n,c,f,d,v) {.name = n,.small = c,.flag = f,.description = d,.value = v,.takes_value=TRUE}

struct option opt(char* n, char s, int f, char* d) {
  struct option output = {s,n,d,f,NULL,false};
  return output;
}
struct option optv(char* n, char s, int f, char* d, void* v, int t) {
  struct value val = {t,v};
  struct option output = {s,n,d,f,val,true};
  return output;
}

#endif
