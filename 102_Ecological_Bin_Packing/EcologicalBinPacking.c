#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COLORS_NUMBER 3
#define BINS 3
#define PERMUTATIONS 6 //3!

void permuteItems(char**,int,int*);
void swap(char*,char*);
long getBottlesSumForPosition(char,int,unsigned int*);
void initializeColorMatrix(char**);
int findIndexOf(char);
int* getBottlesNumberMatrix(char**,int*);
int getMinRow(long*,char**);
unsigned int* splitRow(char*);

int main(){
  int items[COLORS_NUMBER] = {0,1,2};
  int i,j;
  long sum = 0;

  unsigned int* bottles;
  
  long bottlesNumber[PERMUTATIONS] = {0};
  char numbersRow[200];

  char **colorsMatrix = (char**)malloc(sizeof(char*)*PERMUTATIONS);
  for(i=0;i<PERMUTATIONS;i++)  
    colorsMatrix[i] = (char*)malloc(sizeof(char)*COLORS_NUMBER);

  initializeColorMatrix(colorsMatrix);
 
  int row = 0;
  int minRow = 0;
  permuteItems(colorsMatrix,BINS,&row);
  
  while(scanf(" %[^\n]s",numbersRow) != EOF){
    bottles = splitRow(numbersRow);
    for(i=0;i<PERMUTATIONS;i++){
      sum = 0;
      for(j=0;j<COLORS_NUMBER;j++){
        sum += getBottlesSumForPosition(colorsMatrix[i][j],j,bottles);   
      }
      bottlesNumber[i] = sum;
    }
    
    minRow = getMinRow(bottlesNumber,colorsMatrix);

    for(i=0;i<BINS;i++){
      printf("%c",colorsMatrix[minRow][i]);
    }
    printf(" %ld",bottlesNumber[minRow]);
    printf("\n");

    free(bottles);
  }

  for(i=0;i<PERMUTATIONS;i++)
    free(colorsMatrix[i]);

  free(colorsMatrix);
  return 0;
}

void permuteItems(char** colorsMatrix,int n,int* row){
  int i; 
  if(n==0){
    if(*row < PERMUTATIONS-1){
      for(i=0;i<BINS;i++){
        colorsMatrix[*row+1][i] = colorsMatrix[*row][i];
      }
    }
    *row = *row+1;
  }
  else{
    for(i=0;i<n;i++){
      swap(&colorsMatrix[*row][i],&colorsMatrix[*row][n-1]);
      permuteItems(colorsMatrix,n-1,row);
      if(*row < PERMUTATIONS){
        swap(&colorsMatrix[*row][i],&colorsMatrix[*row][n-1]);
      }
    }
  }
}

void swap(char* a,char* b){
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

void initializeColorMatrix(char** colorsMatrix){
  int i,j;

  for(i=0;i<PERMUTATIONS;i++)
    for(j=0;j<COLORS_NUMBER;j++)
      colorsMatrix[i][j] = '0';

  colorsMatrix[0][0] = 'B';
  colorsMatrix[0][1] = 'G';
  colorsMatrix[0][2] = 'C';
}

long getBottlesSumForPosition(char item,int position,unsigned int* bottles){
  long sum = 0;
  int index = findIndexOf(item);
  int bottlePosition = index + (position*BINS);
  
  while(index < BINS*COLORS_NUMBER){
    if(index !=  bottlePosition)
      sum += bottles[index];

    index += BINS;
  }
  
  return sum;  
}

int findIndexOf(char character){
  char colors[3] = {'B','G','C'};
  int i = 0;
  while(colors[i] != character){ i++; }
  return i;
}

int getMinRow(long* bottlesNumber,char** colorsMatrix){
  int i;
  int minRow = 0;
  int minNumber = bottlesNumber[0];

  for(i=1;i<PERMUTATIONS;i++){
    if(bottlesNumber[i] < minNumber){
      minNumber = bottlesNumber[i];
      minRow = i;
    }
    else if(bottlesNumber[i] == minNumber){
      int minColorRow = -1,j=0;  
      while(minColorRow == -1){
        if(colorsMatrix[i][j] < colorsMatrix[minRow][j]){
          minColorRow = i; 
        }
        else if(colorsMatrix[minRow][j] < colorsMatrix[i][j]){
          minColorRow = minRow;
        }
        j++;
      }
      minRow = minColorRow;
    }
  }
  
  return minRow;
}


unsigned int* splitRow(char* row){
  char* token = strtok(row," ");
  unsigned int* numbers = (unsigned int*)malloc(sizeof(unsigned int)*(BINS*COLORS_NUMBER));
  int i=0;

  while(token != NULL){
    sscanf(token,"%u",&numbers[i]);
    token = strtok(NULL," ");
    i++;
  }

  return numbers;
}

