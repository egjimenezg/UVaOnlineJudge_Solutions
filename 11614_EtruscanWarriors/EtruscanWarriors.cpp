#include <stdio.h>
#include <math.h>

long long getEquationRoot(long long c) {
  long long squareRoot = sqrt(1-(4*c));
  return (-1+squareRoot)/2;
}

int main() {
  int cases;
  long long n;
  scanf("%d", &cases);

  while (cases--) {
    //Getting roots of equation (x*(x+1))/2 = n
    //or (x^2)+x-2n = 0
    scanf("%lld", &n);
    long long solution = getEquationRoot(-2*n);
    printf("%lld\n", solution);
  }

  return 0;
}
