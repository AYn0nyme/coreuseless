#include "../include/utils.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char* from_bytes_to_readable(off_t size, int convert) {
  char* output = (char*)malloc(sizeof(char*)+size);

  if(!convert){
    sprintf(output, "%ld", size);
    return output;
  }
  return "";
}

// From https://stackoverflow.com/a/47959703
int pstrcmp(const void *a, const void *b) {
  struct dirent *da = *(struct dirent **)a;
  struct dirent *db = *(struct dirent **)b;
  return strcasecmp(da->d_name, db->d_name);
}


#define BLUE_COLOR "\x1b[34m"
#define GREEN_COLOR "\x1b[32m"
#define RESET_COLOR "\x1b[0m"
#define BOLD "\e[1m"
#define RESET_STYLE "\e[0m"

#define FLAG_NOCOLOR (1 << 0)
#define FLAG_ALL (1 << 1)
#define FLAG_ALMSTALL (1 << 2)
#define FLAG_SIZE (1 << 3)
#define FLAG_SIZE_HMN_RDBL (1 << 4)

const char* usage = "ls (PATH)\nlist all files/directories in current/given PATH";

struct option options[] = {
  opt("nocolor",'c',FLAG_NOCOLOR,"print without colors"),
  opt("all",'a',FLAG_ALL,"print everything including . and .."),
  opt("almost-all",'A',FLAG_ALMSTALL,"print everything except . and .."),
  opt("size",'s',FLAG_SIZE,"get the size of the file/directory"),
  opt("human-readable",'h',FLAG_SIZE_HMN_RDBL,"get the size in a human readable format"),
};

int ls(const char* path, int flags) {
  DIR* dir = opendir(path);
  if(dir == NULL) {
    printf("ls: directory %s does not exists\n", path);
    return 1;
  }
  
  struct dirent* dir_entry;
  int c = 0; struct dirent** buf = calloc(1, sizeof(struct dirent*));

  while((dir_entry = readdir(dir)) != NULL) {
    if((!strcmp(dir_entry->d_name, ".") || !strcmp(dir_entry->d_name, "..")) && !(flags & FLAG_ALL)) continue;
    if(dir_entry->d_name[0]=='.' && ((!(flags & FLAG_ALMSTALL)) && !(flags & FLAG_ALL))) continue;
    buf = reallocarray(buf, c+1, sizeof(struct dirent*));
    buf[c] = malloc(sizeof(struct dirent));
    memcpy(buf[c], dir_entry, sizeof(struct dirent));
    c++;
  }

  qsort(buf, (c), sizeof(struct dirent*), pstrcmp);

  for(int i = 0; i < c; i++) {
    switch(buf[i]->d_type){
      case DT_REG:
        // struct stat stat_buf;
        // stat(buf[i]->d_name, &stat_buf);
        // printf("%s-%ld", buf[i]->d_name, stat_buf.st_size);
        if(flags & FLAG_SIZE) {
          struct stat stat_buf;
          lstat(buf[i]->d_name, &stat_buf);
          char* size = from_bytes_to_readable(stat_buf.st_size, (flags & FLAG_SIZE_HMN_RDBL));
          printf("%s %s", buf[i]->d_name, size);
        }
        if(i+1 < c) putchar(' ');
        break;
      case DT_LNK:
        if(!(flags & FLAG_NOCOLOR)) printf(GREEN_COLOR);
        printf("%s", buf[i]->d_name);
        printf(RESET_COLOR "@");
        if(i+1 < c) putchar(' ');
        break;
      case DT_UNKNOWN:
        break;
      case DT_DIR:
        if(!(flags & FLAG_NOCOLOR)) printf(BLUE_COLOR BOLD);
        printf("%s", buf[i]->d_name);
        printf(RESET_STYLE RESET_COLOR "/");
        if(i+1 < c) putchar(' ');
        break;

    }
  }

  putchar('\n');

  return 0;
}

int main(int argc, char** argv) {
  int flags = parse_args(argc, argv, options, array_len(options));

  if(argc < 2) {
    return ls(".", flags);
  }
  int count=0;
  for(int c = 1; c < argc; c++) {
    if(argv[c][0]=='-')continue;
    count = c; break;
  }
  if(count == 0) {
    return ls(".", flags);
  } else {
    return ls(argv[count], flags);
  }
}
