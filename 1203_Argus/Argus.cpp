#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;
typedef long long int long_int;

typedef struct Query{
  int queryId;
  int period;
  long_int priority;
} Query;

int isNotEndOfQuerys(char*);
bool compare(Query,Query);

int main(){
  int k;
  priority_queue<Query, vector<Query>, decltype(&compare) > queue(&compare);
  char query[100] = "";
  char type[10]="";
  int queryId;
  long long int period;

  while(scanf(" %[^\n]s",query),isNotEndOfQuerys(query)){
    sscanf(query,"%s %d %lld",type,&queryId,&period);
    Query query = {.queryId = queryId, .period = (int)period, .priority = period};
    queue.push(query);
  }
  scanf("%d",&k);

  Query top;

  for(int i=0;i<k;i++){
    top = queue.top();
    queue.pop();
    printf("%d\n",top.queryId);
    top.priority += top.period;
    queue.push(top);
  }
  
  return 0;
}

bool compare(Query q1,Query q2){
  if(q1.priority != q2.priority){
    return q1.priority > q2.priority;
  }
  else{
    return q1.queryId > q2.queryId; 
  }
}

int isNotEndOfQuerys(char* query){
  return strcmp(query,"#") != 0;
}
