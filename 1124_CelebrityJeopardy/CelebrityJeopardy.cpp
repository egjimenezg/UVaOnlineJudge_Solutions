#include <stdio.h>

int main() {

  char s[1024];

  while(scanf("%[^\n]\n", s) != EOF) {
    printf("%s\n", s);
  }

  return 0;
}
