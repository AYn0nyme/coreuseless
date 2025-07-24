#include <stdio.h>
#include <stdlib.h>

const char* usage = "mktemp\nmakes a temporary directory";

int mktempdir() {
  char template[] = "/tmp/tmp.XXXXXX";
  char* tmp_dir = mkdtemp(template);
  if(tmp_dir == NULL) {
    perror("mktemp: ");
    return 1;
  }
  puts(tmp_dir);
  return 0;
}

int main(void) {
  if(mktempdir()) return 1;
}
