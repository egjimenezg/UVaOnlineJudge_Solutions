#include <stdio.h>
#include <iostream>
#include <vector>
#define LSB(n) (n & -n)

using namespace std;

class FenwickTree {
  private:
    vector<int> sequence;
    vector<int> products;
    vector<int> zeros;

  public:
    FenwickTree(int n){
      sequence.assign(n+1, 1); 
      products.assign(n+1, 1);
      zeros.assign(n+1, 0);
    }

    int rpq(int n){
      int product = 1;

      while(n) {
        product *= products[n];
        n -= LSB(n);
      }

      return product;
    }

    int rpq(int a, int b){
      if(a == b){
        return sequence[a];
      }

      if(getZerosInRange(a,b) > 0){
        return 0; 
      }

      return rpq(b)*rpq(a-1);
    }

    void updateCurrentValue(int n, int value){
      while(n < sequence.size()){
        products[n] /= value; 
        n += LSB(n);
      }
    }

    int rsq(int n){
      int sum = 0;

      while(n){
        sum += zeros[n];
        n -= LSB(n);
      }

      return sum;
    }

    int getZerosInRange(int a, int b){
      int lower = (a == 1 ? 0 : rsq(a-1));
      return rsq(b)-lower;
    }

    void updateZeroFrequencies(int n, int value){
      while(n < zeros.size()){
        zeros[n] += value; 
        n += LSB(n);
      } 
    }

    void update(int n, int value) {
      if(sequence[n] == value)
        return;

      int currentValue = sequence[n];
      sequence[n] = value;

      if(currentValue < 0){
        updateCurrentValue(n,currentValue);
      }
      
      if(value == 0){
        updateZeroFrequencies(n, 1);
      }
      else{
        if(currentValue == 0){
          updateZeroFrequencies(n, -1);
        }
        while(n < sequence.size()){
          products[n] *= value;
          n += LSB(n);
        }
      }
    }
    
};

int getNumber(int X){
  if(X < 0)
    return -1;

  if(X > 0)
    return 1;

  return 0;
}

int main(){
  int N,K, X;
  char commandType;
  int I,J;

  while(scanf("%d %d",&N,&K) != EOF){

    FenwickTree fenwickTree(N);
    string result;

    for(int i=0; i<N; i++){
      scanf("%d",&X);
      fenwickTree.update(i+1,getNumber(X));
    }

    for(int i=0; i<K; i++){
      scanf("\n%c %d %d", &commandType, &I, &J);
      if(commandType == 'P'){
        int queryResult = fenwickTree.rpq(I, J);
        if(queryResult < 0){
          result += "-"; 
        }
        else if(queryResult > 0){
          result += "+"; 
        }
        else{
          result += "0"; 
        }
      }
      else{
        fenwickTree.update(I, getNumber(J));
      }
    }

    cout << result << endl;
  }

  return 0;
}
