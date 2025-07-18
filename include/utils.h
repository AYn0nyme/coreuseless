#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <stddef.h>

int parse_args(int argc, char** argv, struct option options[], size_t options_count);

#define array_len(array) (sizeof(array) / sizeof(*array))

#endif
