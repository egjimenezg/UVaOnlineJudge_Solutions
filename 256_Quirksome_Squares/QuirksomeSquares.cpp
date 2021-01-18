#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<vector<long> > calculateSolution();

int main(){
  int n;

  vector<vector<long> > solutions = calculateSolution();

  while(scanf("%d", &n) != EOF){
    printf("%0.*d\n%0.*d\n",n, 0, n, 1);

    for(int index=solutions[n/2-1].size()-1;index>=0;index--){
      printf("%0.*ld\n",n, solutions[n/2-1][index]);
    }
  }

}

vector<vector<long> > calculateSolution(){
  vector<vector<long> > solution(4);

  for(int a=9999;a>=1;a--){
    for(int b=1;b<a;b++){
      long x = (a+b)*(a+b);
      
      if(x == (a*10+b) || x == (b*10+a)){
        solution[0].push_back(x);
      }
      else if(x == (a*10^2+b) || x == (b*10^2+a)){
        solution[1].push_back(x);
      }
      else if(x == (a*10^3+b) || x == (b*10^3+a)){
        solution[2].push_back(x);
      }
      else if(x == (a*10^4+b) || x == (b*10^4+a)){
        solution[3].push_back(x);
      }
    }
  }

  return solution;
}
