#include <stdio.h>

int main() {
  int T, n, m;
  long long minNumberOfTries;

  scanf("%d", &T);

  while(T--) {
    scanf("%d %d", &n, &m); 
    minNumberOfTries = (m-n)*n + ((n-1)*n)/2;
    printf("%lld\n", minNumberOfTries);
  }	

  return 0;
}
