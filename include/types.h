#ifndef TYPES_H
#define TYPES_H

#include <ncurses.h>
#include <sys/types.h>

#define TYPE_STRING 0
#define TYPE_INT    1
#define TYPE_BOOL   2

struct value {
  uint8_t type ;
  void*   value;
};

struct option {
  char         small      ;
  char*        name       ;
  char*        description;
  int          flag       ;
  struct value value      ;
  bool         takes_value;
};

struct parsed {
  int          flags  ;
  struct value value[];
};

#endif
