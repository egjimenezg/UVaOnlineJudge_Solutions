#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 25
#define ACTION_SIZE 5
#define POSITION_SIZE 5

typedef struct Instruction{
  char action[ACTION_SIZE];
  char position[POSITION_SIZE];
  int origin;
  int destiny;
  struct Instruction *next;
} Instruction;

typedef struct Block{
  int value;
  int currentStack; 
} Block;

typedef struct Stack{
  int size;
  int data[SIZE];
} Stack;

typedef struct List{
  Instruction* head;
} List;

char* readInstruction();
List createInstructionsList();
Instruction* createInstruction(char*);
int isNotQuitInstruction(char*,char*);
void addInstructionToList(char*,List*);

void executeInstructions(List*,Block*,Stack*);
Block* createBlocks(int);
void initializeStacks(Stack*,int);
int isMoveOntoInstruction(char*,char*);
int isMoveOverInstruction(char*,char*);
int isPileOntoInstruction(char*,char*);
int isPileOverInstruction(char*,char*);
void moveOnto(int,int,Block*,Stack*);
void moveOver(int,int,Block*,Stack*);
void pileOnto(int,int,Block*,Stack*);
void pileOver(int,int,Block*,Stack*);
void push(Stack*,int);
int pop(Stack*);
int isEmpty(Stack*);
void printStacks(Stack*,Block*,int);

int main(){
  int n;
  char instruction[20];
  char action[ACTION_SIZE];

  List instructions = createInstructionsList();

  scanf("%d",&n);
  Stack* stacks = (Stack*)malloc(sizeof(Stack)*n);
  initializeStacks(stacks,n);

  Block* blocks = createBlocks(n);
  
  while(isNotQuitInstruction(instruction,action)){
    addInstructionToList(instruction,&instructions);
  }
  
  executeInstructions(&instructions,blocks,stacks);
  printStacks(stacks,blocks,n);

  return 0;
}

List createInstructionsList(){
  List list;
  list.head = NULL;
  return list;
}

Block* createBlocks(int n){
  Block* blocks = (Block*)malloc(sizeof(Block)*n);
  int i;
  for(i=0;i<n;i++){
    blocks[i].value = i;
    blocks[i].currentStack = i;
  }
  return blocks;
}

void initializeStacks(Stack* stacks,int n){
  int i;
  for(i=0;i<n;i++){
    stacks[i].size = 0;
    push(&stacks[i],i);
  }
}

int isNotQuitInstruction(char* instruction,char* action){
  scanf(" %[^\n]s",instruction);
  strncpy(action,instruction,ACTION_SIZE-1);
  action[ACTION_SIZE-1] = '\0';
  return (strcmp(action,"quit") != 0);
}

Instruction* createInstruction(char* instructionText){
  Instruction* newInstruction = (Instruction*)malloc(sizeof(Instruction));
  sscanf(instructionText,"%s %d %s %d",newInstruction->action,
                                       &(newInstruction->origin),
                                       newInstruction->position,
                                       &(newInstruction->destiny));
  newInstruction->next = NULL;
  return newInstruction;
}

void addInstructionToList(char* instruction,List* instructionsList){

  if(instructionsList->head == NULL){
    instructionsList->head  = createInstruction(instruction);
    return;
  }

  Instruction* tail = instructionsList->head;

  while(tail->next != NULL)
    tail = tail->next; 

  tail->next = createInstruction(instruction);
  return;
}

void push(Stack* stack,int data){
  stack->data[stack->size++] = data;
}

int pop(Stack* stack){
  stack->size--;
  return stack->data[stack->size];
}

int isEmpty(Stack* stack){
  return stack->size == 0;
}

void executeInstructions(List* instructions,Block* blocks,Stack* stacks){
  Instruction* instruction = instructions->head;
  while(instruction != NULL){
    
    if(isMoveOntoInstruction(instruction->action,instruction->position)){
      moveOnto(instruction->origin,instruction->destiny,blocks,stacks);
    }
    else if(isMoveOverInstruction(instruction->action,instruction->position)){
      moveOver(instruction->origin,instruction->destiny,blocks,stacks);
    }
    else if(isPileOntoInstruction(instruction->action,instruction->position)){
      pileOnto(instruction->origin,instruction->destiny,blocks,stacks);
    }
    else if(isPileOverInstruction(instruction->action,instruction->position)){
      pileOver(instruction->origin,instruction->destiny,blocks,stacks);
    }

    instruction = instruction->next;
  }

}

void moveOnto(int origin,int destiny,Block* blocks,Stack* stacks){
  Block* a = &blocks[origin];
  Block* b = &blocks[destiny];

  if(a->currentStack != b->currentStack){
    Stack* originStack = &stacks[a->currentStack];
    Stack* destinyStack = &stacks[b->currentStack];
    int top;

    while((top = pop(originStack)) != origin){
      Block* block = &blocks[top];
      block->currentStack = block->value;
      push(&stacks[block->currentStack],block->value);
    }

    while(destinyStack->data[destinyStack->size-1] != destiny){
      Block* block = &blocks[pop(destinyStack)];
      block->currentStack = block->value;
      push(&stacks[block->currentStack],block->value);
    }

    push(destinyStack,a->value);
    a->currentStack = b->currentStack;
  }
}

void moveOver(int origin,int destiny,Block* blocks,Stack* stacks){
  Block* a = &blocks[origin];
  Block* b = &blocks[destiny];

  if(a->currentStack != b->currentStack){
    Stack* originStack = &stacks[a->currentStack];
    Stack* destinyStack = &stacks[b->currentStack];
    int top;

    while((top = pop(originStack)) != origin){
      Block* block = &blocks[top];
      block->currentStack = block->value;
      push(&stacks[block->currentStack],block->value);
    }
 
    push(destinyStack,a->value);
    a->currentStack = b->currentStack;
  }
}

void pileOnto(int origin,int destiny,Block* blocks,Stack* stacks){
  Block* a = &blocks[origin];
  Block* b = &blocks[destiny];

  if(a->currentStack != b->currentStack){
    Stack* swapStack = (Stack*)malloc(sizeof(Stack));
    swapStack->size = 0;
    Stack* originStack = &stacks[a->currentStack];
    Stack* destinyStack = &stacks[b->currentStack];
    int top;

    do{
      top = pop(originStack);
      push(swapStack,top);
    }
    while(top != origin);
    
    while(destinyStack->data[destinyStack->size-1] != destiny){
      Block* block = &blocks[pop(destinyStack)];
      block->currentStack = block->value;
      push(&stacks[block->currentStack],block->value);
    }

    while(!isEmpty(swapStack)){
      Block* currentBlock = &blocks[pop(swapStack)];
      push(destinyStack,currentBlock->value);
      currentBlock->currentStack = b->currentStack;  
    }
  }
}

void pileOver(int origin,int destiny,Block* blocks,Stack* stacks){
  Block* a = &blocks[origin];
  Block* b = &blocks[destiny];

  if(a->currentStack != b->currentStack){
    Stack* swapStack = (Stack*)malloc(sizeof(Stack));
    swapStack->size = 0;
    Stack* originStack = &stacks[a->currentStack];
    Stack* destinyStack = &stacks[b->currentStack];
    int top;

    do{
      top = pop(originStack);
      push(swapStack,top);
    }
    while(top != origin);

    while(!isEmpty(swapStack)){
      Block* block = &blocks[pop(swapStack)];
      push(destinyStack,block->value);
      block->currentStack = b->currentStack;
    }
  }
}

void printStacks(Stack* stacks,Block* blocks,int n){
  int i,j;
  for(i=0;i<n;i++){
    printf("%d:",i);
    for(j=0;j<stacks[i].size;j++)
      printf(" %d",stacks[i].data[j]);
    printf("\n");
  }
}

int isMoveOntoInstruction(char* action,char* position){
  return (strcmp(action,"move") == 0 && strcmp(position,"onto") == 0);
}

int isMoveOverInstruction(char* action,char* position){
  return (strcmp(action,"move") == 0 && strcmp(position,"over") == 0);
}

int isPileOntoInstruction(char* action,char* position){
  return (strcmp(action,"pile") == 0 && strcmp(position,"onto") == 0);
}

int isPileOverInstruction(char* action,char* position){
  return (strcmp(action,"pile") == 0 && strcmp(position,"over") == 0);
}

