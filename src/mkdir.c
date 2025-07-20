#include "../include/utils.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define FLAG_PARENTS (1 << 0)
#define FLAG_VERBOSE (1 << 1)

const char* usage = "mkdir [DIRECTORY...]\nmake a/multiple DIRECTORY.IES";

struct option options[] = {
  opt("parents",'p',FLAG_PARENTS,"create parents if needed"),
  opt("verbose",'i',FLAG_VERBOSE,"get more infos"),
};

int mkdirectory(char* path, int flags) {
  char* first_path = strtok(path, "/");
  DIR* dir = opendir(first_path);
  if(dir != NULL) {
    closedir(dir);
    printf("mkdir: %s already exists\n", path);
    return 1;
  }
  char* second_path = strtok(NULL, "/");
  if(second_path != NULL && !(flags & FLAG_PARENTS)) {
    printf("mkdir: cannot create %s because its parent.s does not exist", path);
    return 1;
  }
  if(mkdir(path, 0777)) {
    printf("mkdir: could not create %s\n", path);
    return 1;
  }
  if(flags & FLAG_VERBOSE) printf("mkdir: created %s\n", path);
  return 0;
}

int main(int argc, char** argv) {
  int flags = parse_args(argc, argv, options, array_len(options));

  if(argc < 2) {
    puts("mkdir: need at least 1 argument");
    return 1;
  }
  for(int c = 1; c < argc; c++) {
    if(argv[c][0]=='-')continue;
    if(mkdirectory(argv[c], flags)) return 1;
  }
}
