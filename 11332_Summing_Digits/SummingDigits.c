#include <stdio.h>

int getSingleDigitNumber(long);

int main(){
  long n;

  while(scanf("%ld",&n), n){
    printf("%d\n",getSingleDigitNumber(n));
  }

  return 0;
}

int getSingleDigitNumber(long n){
  int times = 0;
  long sum = 0;

  while(n >= 1){
    sum += n%10;
    n = n/10;
    times++;
  }

  if(times == 1)
    return sum;
  else
    return getSingleDigitNumber(sum);

}
