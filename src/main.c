#include <stdio.h>

static int main2() {
  puts("Hello World!");
  return 0;
}

int main() {
  int res = main2();
  puts("Exiting :3");
  return res;
}

