#include <stdio.h>
#include <vector>
#define left(position) ( (position<<1)+1 )
#define right(position) ( (position<<1)+2 )

using namespace std;
typedef long int long_int;

typedef struct Range {
  long left;
  long right;
  long index;
} Range;

typedef struct Node {
  long_int number;
  long_int frequency;
  long_int left;
  long_int right;
} Node;

class SegmentTree {
  private:
    vector<Range> tree;
    vector<long_int> data;
    vector<Node> frequencies;
    long_int n;

    vector<Node> getFrequencies(){
      vector<Node> frequenciesList;
      long_int dataSize = data.size();

      Node currentNode = {.number = data[0], .frequency = 1,
                          .left = 0, .right = 0};
      long_int i = 1;

      for(i=1;i<dataSize;i++){
        if(currentNode.number == data[i]){
          currentNode.frequency++;
          currentNode.right++;
        }
        else{
          frequenciesList.push_back(currentNode);
          currentNode.number = data[i];
          currentNode.frequency = 1;
          currentNode.left = i;
          currentNode.right = i;
        }
      }

      frequenciesList.push_back(currentNode);

      return frequenciesList;
    }


    void build(long_int position,long_int L,long_int R){
      if(L == R){
        Range leaf;
        leaf.index = L;
        leaf.left = frequencies[L].left;
        leaf.right = frequencies[L].right;

        tree[position] = leaf;
      }
      else{
        build(left(position),L,(L+R)/2);
        build(right(position),(L+R)/2+1,R);
        
        Range p1 = tree[left(position)];
        Range p2 = tree[right(position)];
      
        Range root = {.left = p1.left,
                      .right = p2.right};
                      
        root.index = (frequencies[p1.index].frequency >= frequencies[p2.index].frequency) ? p1.index : p2.index;

        tree[position] = root;
      }
    }

    long_int rmq(long_int position, long_int L, long_int R, long_int i, long_int j){
      if(i == j)
        return 1;
      
      long_int rangeMaxIndex = tree[position].index;

      if(i > frequencies[rangeMaxIndex].right || j < frequencies[rangeMaxIndex].left){
        if(L == R){
          return -1;
        }
        
        if(tree[left(position)].right >= j){
          return rmq(left(position),L,(L+R)/2,i,j);
        }
        else if(tree[right(position)].left <= i){
          return rmq(right(position),(L+R)/2+1,R,i,j);
        }
        else{
          return max(rmq(left(position),L,(L+R)/2,i,tree[left(position)].right),
                     rmq(right(position),(L+R)/2+1,R,tree[right(position)].left,j));
        }

      }

      if((i <= tree[position].left && tree[position].right <= j) ||
         (i <= frequencies[rangeMaxIndex].left && j >= frequencies[rangeMaxIndex].right)){
        return frequencies[rangeMaxIndex].frequency;
      }

      if(frequencies[rangeMaxIndex].left <= i && j <= frequencies[rangeMaxIndex].right){
        return j-i+1;
      }
      
      long_int maxRange = 0;

      if(i >= frequencies[rangeMaxIndex].left && i <= frequencies[rangeMaxIndex].right){
        maxRange = frequencies[rangeMaxIndex].right-i+1;

        if(L != R){
          if(tree[right(position)].left <= frequencies[rangeMaxIndex].right+1){
            maxRange = max(maxRange,
                           rmq(right(position),(L+R)/2+1,R,frequencies[rangeMaxIndex].right+1,j));
          }

          if(frequencies[rangeMaxIndex].right+1 <= tree[left(position)].right){
            if(j <= tree[left(position)].right){
              maxRange = max(maxRange,
                             rmq(left(position),L,(L+R)/2,frequencies[rangeMaxIndex].right+1,j));
            }
            else{
              maxRange = max(maxRange,
                             rmq(left(position),L,(L+R)/2,
                                 frequencies[rangeMaxIndex].right+1,
                                 tree[left(position)].right));

              maxRange = max(maxRange,
                             rmq(right(position),(L+R)/2+1,R,
                                  tree[right(position)].left,j));
            }
          }
        }
      }

      if(j <= frequencies[rangeMaxIndex].right && 
         j >= frequencies[rangeMaxIndex].left){

        maxRange = j-frequencies[rangeMaxIndex].left+1;

        if(L != R){
          if(tree[left(position)].right >= frequencies[rangeMaxIndex].left-1){
            maxRange = max(maxRange,
                           rmq(left(position),L,(L+R)/2,i,frequencies[rangeMaxIndex].left-1));
          }

          if(tree[right(position)].left <= frequencies[rangeMaxIndex].left-1) {
            if(i >= tree[right(position)].left){
              maxRange = max(maxRange,
                             rmq(right(position),(L+R)/2+1,R,i,frequencies[rangeMaxIndex].left-1));
            }
            else{
              maxRange = max(maxRange,
                             rmq(right(position),(L+R)/2+1,R,
                                 tree[right(position)].left,frequencies[rangeMaxIndex].left-1));

              maxRange = max(maxRange,
                             rmq(left(position),L,(L+R)/2,i,tree[left(position)].right));
            }
          }
        }
      }
      
      return maxRange;
    }
    
  public:
    SegmentTree(const vector<long_int> &_data){
      data = _data;
      frequencies = getFrequencies();
      n = frequencies.size();
      tree.resize(4*n);
      build(0,0,n-1); 
    }

    long_int rmq(long_int i, long_int j){
      return rmq(0,0,n-1,i-1,j-1);
    }

};

int main(){
  long_int n,q,i,j;

  while(scanf("%ld %ld",&n,&q),n){
    vector<long_int> data(n);

    for(long_int k=0;k<n;k++){
      scanf("%ld",&data[k]);
    }
    
    SegmentTree segmentTree(data);

    while(q--){
      scanf("%ld %ld",&i,&j);
      printf("%ld\n",segmentTree.rmq(i,j));
    }
  }
}

