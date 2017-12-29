#include <stdio.h>
#include <bitset>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#define SIZE 26

using namespace std;

typedef vector<int> neighbors;
typedef vector< neighbors > adjacencyList;
int startsWithAsterisk(string);
vector<int> getLetters(string);

int main(){
  int T;
  scanf("%d",&T);
  string s;

  while(T--){
    bitset<SIZE> nodes;   
    adjacencyList graph(SIZE);
    vector<int> queue;

    int numberOfTrees = 0,
        acorns = 0;

    while( (cin >> s), !startsWithAsterisk(s)){
      graph.at(s.at(1)-65).push_back(s.at(3)-65);
      graph.at(s.at(3)-65).push_back(s.at(1)-65);
    }
    
    cin >> s; 
    vector<int> letters = getLetters(s); 
    queue.push_back(letters.at(0));

    for(int i=0;i<letters.size();i++){
      if(graph.at(letters[i]).empty()){
        acorns++;
      }
      else if(!nodes[letters[i]]){
        queue.push_back(letters[i]);
        while(!queue.empty()){
          int node = queue.at(0);  
          queue.erase(queue.begin());

          for(int j=0;j<graph[node].size();j++){
            if(!nodes[graph[node][j]]){
              queue.push_back(graph[node][j]);
              nodes.set(graph[node][j],1);
            }
          }
        }
        nodes.set(letters[i],1);
        numberOfTrees++;
      }
    }

    printf("There are %d tree(s) and %d acorn(s).\n",numberOfTrees,acorns);
  }

  return 0;
}

int startsWithAsterisk(string s){
  return s.find("*") != string::npos;
}

vector<int> getLetters(string text){
  int position = 0;
  vector<int> letters;
  istringstream stringstream(text);
  string letter;

  while(std::getline(stringstream,letter,',')){
    letters.push_back(letter.at(0)-65);
  }

  return letters;
}
