#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

vector<int> getData(string);

class SegmentTree {
  private:
    vector<int> segmentTree;
    vector<char> lazy;
    vector<int> data;
    int n;

    int left(int position){
      return (position<<1)+1;
    }

    int right(int position){
      return (position<<1)+2;
    }

    void build(int position,int L,int R){
      if(L == R){
        segmentTree[position] = data[L];
      }
      else{
        build(left(position),L,(L+R)/2);
        build(right(position),(L+R)/2+1,R);
        segmentTree[position] = segmentTree[left(position)] + segmentTree[right(position)];
      }
    }

    int getLazyValue(char type,int currentValue,int L,int R){
      if(type == 'I')
        return ((R-L+1)-currentValue);

      if(type == 'F')
        return (R-L+1);

      return 0;
    }

    char getUpdatedSegmentType(char currentType){
      switch(currentType){
        case 'I':
         return '0';
        case 'F':
         return 'E';
        case 'E':
         return 'F';
        default:
         return 'I';
      }
    }

    void assignLazyTypes(char type,int position,int L,int R){
      if(L != R){
        if(type  == 'E' || type == 'F'){
          lazy[left(position)] = type;
          lazy[right(position)] = type;
        }
        else{
          lazy[left(position)] = getUpdatedSegmentType(lazy[left(position)]);
          lazy[right(position)] = getUpdatedSegmentType(lazy[right(position)]);
        }
      }
    }

    void updateRange(int position,int i,int j,
                     char type,int L,int R){

      if(lazy[position] != '0'){
        segmentTree[position] = getLazyValue(lazy[position],segmentTree[position],L,R);
        assignLazyTypes(lazy[position],position,L,R);
        lazy[position] = '0';
      }

      if(j < L || i > R)
        return;

      if(i <= L && j >= R){
        segmentTree[position] = getLazyValue(type,segmentTree[position],L,R);
        assignLazyTypes(type,position,L,R);
        return;
      }

      updateRange(left(position),i,j,type,L,(L+R)/2);
      updateRange(right(position),i,j,type,(L+R)/2+1,R);

      segmentTree[position] = segmentTree[left(position)] + segmentTree[right(position)];
    }

    int rsq(int position,int i,int j,int L, int R){
      if(lazy[position] != '0'){
        segmentTree[position] = getLazyValue(lazy[position],segmentTree[position],L,R);
        assignLazyTypes(lazy[position],position,L,R);
        lazy[position] = '0';
      }

      if(j < L || i > R)
       return 0;
      
      if(L >= i && j >= R)
        return segmentTree[position];
 
      return rsq(left(position),i,j,L,(L+R)/2) + rsq(right(position),i,j,(L+R)/2+1,R);
    }
    
  public:

    void updateRange(int i,int j,char type){
      updateRange(0,i,j,type,0,n-1);
    }

    int rsq(int i,int j){
      return rsq(0,i,j,0,n-1);
    }

    SegmentTree(const vector<int> &data){
      this->data = data;
      n = data.size();
      segmentTree.assign(n*4,0);
      lazy.assign(n*4,'0');
      build(0,0,n-1);
    }
};

int main(){

  int T,M,Ts,Q,a,b,queryNumber;
  char type;

  scanf("%d",&T);

  for(int caseNumber=1;caseNumber<=T;caseNumber++){
    stringstream s;
    scanf("%d",&M); 

    while(M--){
      string pirates;
      scanf("%d\n",&Ts);

      getline(cin,pirates);

      for(int i=0;i<Ts;i++){
        s << pirates;        
      }
    }

    SegmentTree segmentTree(getData(s.str()));

    scanf("%d\n",&Q);
    queryNumber = 1;

    printf("Case %d:\n",caseNumber);

    while(Q--){ 
      scanf("%c %d %d\n",&type,&a,&b);
      if(type == 'S'){
        printf("Q%d: %d\n",queryNumber++,segmentTree.rsq(a,b));    
      }
      else{
        segmentTree.updateRange(a,b,type);
      }
    }
  }

  return 0;
}

vector<int> getData(string s){
  vector<int> data;

  for(int i=0;i<s.size();i++)
    data.push_back(s[i]-'0'); 
 
  return data;
}
