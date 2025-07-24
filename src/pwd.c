#include <stdio.h>
#include <stdlib.h>
const char* usage = "pwd\nget the current working directory";

int main() {
  char* pwd = getenv("PWD");
  if(pwd == NULL) {
    puts("pwd: PWD env not set");
    return 1;
  }
  puts(pwd);
}
