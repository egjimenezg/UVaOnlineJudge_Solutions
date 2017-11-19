#include <stdio.h>
#include <stdlib.h>

int getMaxOfArray(int*,int);
int getCycleLength(int);
int isOdd(int);

int main(){
  
  int p,q;

  while((scanf("%d %d",&p,&q) != EOF)){
    int size = abs(q-p)+1,i;
    int numbers[size];
    int lowest = p < q ? p : q; 

    for(i=0;i< size;i++)
      numbers[i] = getCycleLength(lowest+i);
    
    printf("%d %d %d\n",p,q,getMaxOfArray(numbers,size));
  }

  return 0;
}

int getCycleLength(int n){
  int cycleLength = 1;

  while(n > 1){
    if(isOdd(n))
      n = 3*n+1;
    else
      n = n/2;

    cycleLength++;
  }

  return cycleLength;
}

int getMaxOfArray(int* A,int size){
  int i,maxNumber=A[0];

  for(i=1;i<size;i++){
    if(A[i]>maxNumber)
      maxNumber = A[i];
  }

  return maxNumber;
}

int isOdd(int n){
  return (n%2 != 0);
}
