#include <stdio.h>

int getDegrees(int,int,int,int);

int main(){
  int initialPosition,n1,n2,n3;
  
  while(scanf("%d %d %d %d",&initialPosition,&n1,&n2,&n3), (initialPosition || n1 || n2 || n3))
    printf("%d\n",getDegrees(initialPosition,n1,n2,n3));

  return 0;
}

int getDegrees(int initialPosition,int n1, int n2, int n3){
  return 1080+(((initialPosition+40-n1)%40)*9)+(((n2+40-n1)%40)*9)+(((n2+40-n3)%40)*9);
}
