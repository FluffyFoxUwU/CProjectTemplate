#include <stdlib.h>
#include <stdio.h>

#include "util/util.h"

int main2(int argc, char** argv) {
  util_init();
  
  printf("Hello World!\n");
  
  util_cleanup();
  return EXIT_SUCCESS;
}

