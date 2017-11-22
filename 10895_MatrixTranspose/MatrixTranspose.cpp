#include <stdio.h>
#include <deque>
#include <vector>

using namespace std;

typedef pair<int,int> Neighbor;
typedef deque<Neighbor> Neighbors;
typedef vector<Neighbors> AdjacencyList;

AdjacencyList createGraph(int);
AdjacencyList getTranspose(int,AdjacencyList*);
void printTranspose(int,int,AdjacencyList*);

int main(){
	int rows,cols;
	int i,j;
	while(scanf("%d %d",&rows,&cols) != EOF){
	  AdjacencyList graph = createGraph(rows);
	  AdjacencyList transpose =  getTranspose(cols,&graph);
	  printTranspose(cols,rows,&transpose);
  }
  return 0;
}

AdjacencyList createGraph(int rows){
	AdjacencyList graph(rows);
	int r,i,columnIndex,rowIndex,columnValue;

	for(rowIndex=0;rowIndex<rows;rowIndex++){
		scanf("\n%d",&r);

		for(i=0;i<r;i++){
			scanf("%d ",&columnIndex);
			graph[rowIndex].push_back(make_pair(columnIndex,0));
		}

		for(i=0;i<r;i++){
			scanf("%d ",&columnValue);
			graph[rowIndex][i].second = columnValue;
		}

	}

	return graph;
}

AdjacencyList getTranspose(int rows,AdjacencyList* adjacencyList){
	AdjacencyList transpose;
	int rowIndex,colIndex;

	if(adjacencyList->size()){
		transpose.resize(rows);

		for(rowIndex=0;rowIndex<rows;rowIndex++){
			for(colIndex=0;colIndex<adjacencyList->size();colIndex++){
				if(adjacencyList->at(colIndex).size()){
					Neighbor neighbor = adjacencyList->at(colIndex).front();

					if(neighbor.first == rowIndex+1){
						neighbor.first = colIndex+1;
						transpose[rowIndex].push_back(neighbor);
						adjacencyList->at(colIndex).pop_front();
					}
				}
			}
		}

	}

	return transpose;		
}

void printTranspose(int rows,int cols,AdjacencyList* transpose){
	printf("%d %d\n",rows,cols);
	int rowsIndex,columnsIndex;

	for(rowsIndex=0;rowsIndex<rows;rowsIndex++){
		if(transpose->size()){
			printf("%lu",transpose->at(rowsIndex).size());
			for(columnsIndex=0;columnsIndex<transpose->at(rowsIndex).size();columnsIndex++){
				printf(" %d",transpose->at(rowsIndex)[columnsIndex].first);
			}
			printf("\n");
			for(columnsIndex=0;columnsIndex<transpose->at(rowsIndex).size();columnsIndex++){
				printf("%s%d",columnsIndex > 0 ? " " : "",transpose->at(rowsIndex)[columnsIndex].second);
			}
			printf("\n");
		}
		else{
			printf("0\n\n");
		}
	}

}
