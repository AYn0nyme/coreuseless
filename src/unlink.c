#include <stdio.h>
#include <unistd.h>
const char* usage = "unlink [FILE...]\nunlink all FILE.s"; 

int main(int argc, char** argv) {
  int count = 0;
  for(int c = 1; c < argc; c++) {
    count++;
    if(unlink(argv[c])) return 1;
  }
  if(count == 0) {
    puts("unlink: no files provided");
    return 1;
  }
}
