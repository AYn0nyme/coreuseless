// Code from SnowsSky

#include <stdio.h>

const char* usage = "nl [FILE]\nget the content of the file with the number of the lines";

int main(int argc, char** argv) {
  char* file = argv[1];
  
  FILE* f = fopen(file, "r");    
  if(f == NULL) {
    printf("nl: cannot open file %s", file);
    return 1;
  };
  int count = 0;
  char line[2048];
  while (fgets(line, sizeof(line), f)) { 
    count++;
    printf("%d. %s", count, line);           
  }
}
