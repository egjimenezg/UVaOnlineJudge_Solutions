#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct Book{
  char author[80];
  char title[100];
  char status[10];
  bool operator==(const char* titleToSearch){
    return (strcmp(title,titleToSearch) == 0);
  }
} Book;

bool compare(const Book &bookA,const Book &bookB){
  if(strcmp(bookA.author,bookB.author) != 0)
    return strcmp(bookA.author,bookB.author) < 0;
  else
    return strcmp(bookA.title,bookB.title) < 0;
}

void createBook(Book*,char*,long);

int isNotWord(char*,char*);

int main(){

  vector<Book> books;

  char text[200];
  char action[8];
  char title[100];
  char status[8];
  char word[10];
  strcpy(word,"END");

  while(isNotWord(text,word)){
    char *quotes = NULL;
    quotes = strchr(text,'"');
    quotes = strchr(quotes+1,'"');
    Book* book = new Book();
    createBook(book,text,quotes-text+1);
    books.push_back(*book);
  }

  sort(books.begin(),books.end(),compare);

  while(isNotWord(text,word)){
    strncpy(action,text,6);
    strncpy(title,text+7,strlen(text));
    
    if((strcmp(action,"BORROW") == 0) || (strcmp(action,"RETURN") == 0)){
      vector<Book>::iterator bookFound = find(books.begin(),books.end(),title);
      strcpy(status,action);
      strcat(status,"ED");
      strcpy(bookFound->status,status);
    }
    else{
      long previous = -1;

      for(long i=0;i < books.size() ; i++){
        if(strcmp(books.at(i).status,"SHELVED") == 0){
          previous = i;
        }
        else if(strcmp(books.at(i).status,"RETURNED") == 0){
          if(previous >= 0){
            printf("Put %s after %s\n",books.at(i).title,books.at(previous).title);
          }
          else{
            printf("Put %s first\n",books.at(i).title);
          }

          previous = i;

          strcpy(books.at(i).status,"SHELVED");
        }
      }
      printf("END\n");
    }
  }

  return 0;
}

void createBook(Book* book,char* text,long position){
  strncpy(book->title,text,position);
  strncpy(book->author,text+position+4,strlen(text));
  strcpy(book->status,"SHELVED");
}

int isNotWord(char* text,char* word){
  scanf("\n%[^\n]s",text);
  return (strcmp(text,word) != 0);
}
