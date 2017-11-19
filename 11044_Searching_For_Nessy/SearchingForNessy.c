#include <stdio.h>

int getSonarBeams(int,int);

int main(){
  int cases,n,m;
  scanf("%d",&cases);

  while(cases--){
    scanf("%d %d",&n,&m);
    printf("%d\n",getSonarBeams(n-2,m-2));
  }

  return 0;
}

int getSonarBeams(int n,int m){
  int sonarBeams = (m/3) + ((m%3 != 0) ? 1 : 0);
  sonarBeams *= (n/3) + ((n%3 != 0) ? 1 : 0);
  return sonarBeams;
}
