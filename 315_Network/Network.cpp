#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#define UNVISITED -1

using namespace std;

class Graph {

  private:
    vector<int> dfs_num, dfs_low, dfs_parent, articulation_vertex;
    vector<vector<int> > adjacencyList;
    int dfsCounter, dfsRoot, rootChildren;

  public:
    Graph(int n) {
      dfs_num.assign(n, UNVISITED);
      dfs_low.assign(n, 0);
      dfs_parent.assign(n, 0);
      articulation_vertex.assign(n, 0);
      adjacencyList.resize(n);
      dfsCounter = 0;
    }

    ~Graph();

    int getArticulationPoints() {
      int articulationNodes = 0;

      for (int node=0; node < adjacencyList.size(); node++) {
        if (dfs_num[node] == UNVISITED) {
          dfsRoot = node;
          rootChildren = 0;
          articulationPoints(node);
          articulation_vertex[dfsRoot] = (rootChildren > 1);
        }
      }

      for (int node=0; node < articulation_vertex.size(); node++) {
        if (articulation_vertex[node] == 1) {
          articulationNodes++;
        }
      }

      return articulationNodes;
    }

    void addEdge(int u, int v) {
      adjacencyList[u-1].push_back(v-1);
    }

    void articulationPoints(int source) {
      dfs_low[source] = dfs_num[source] = dfsCounter++;

      for(int neighbor=0; neighbor < adjacencyList[source].size(); neighbor++) {
        int v = adjacencyList[source][neighbor];

        if (dfs_num[v] == UNVISITED) {
          dfs_parent[v] = source;
          if (source == dfsRoot) rootChildren++;
          articulationPoints(v);
          
          if (dfs_low[v] >= dfs_num[source]) {
            articulation_vertex[source] = 1;
          }

          dfs_low[source] = min(dfs_low[source], dfs_low[v]);
        }
        else if (v != dfs_parent[source]){
          dfs_low[source] = min(dfs_low[source], dfs_num[v]);   
        }
      }
    }
};

vector<int> getNeighbors(string nodes) {
  vector<int> neighbors;
  size_t position = 0;
  string node;

  while((position = nodes.find(" ")) != string::npos){
    node = nodes.substr(0, position);
    neighbors.push_back(stoi(node));
    nodes.erase(0, position + 1);
  }
  
  neighbors.push_back(stoi(nodes.substr(0, nodes.size())));

  return neighbors;
}

int main() {
  int nodesNumber, node;

  while(scanf("%d\n", &nodesNumber) != EOF) {
    if (nodesNumber != 0) {
      Graph* graph = new Graph(nodesNumber);
      string neighbors;

      while(getline(cin, neighbors) && neighbors.compare("0")) {
        vector<int> nodesList = getNeighbors(neighbors);      
        
        for(int index=1; index < nodesList.size(); index++) {
          graph->addEdge(nodesList[0], nodesList[index]);
          graph->addEdge(nodesList[index], nodesList[0]);
        }
      }

      printf("%d\n", graph->getArticulationPoints());
    }
  }

  return 0;
}
