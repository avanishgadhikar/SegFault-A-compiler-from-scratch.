#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define SIZEVAR 20

typedef struct DataItemVar {
    size_t data;
    char* key;
}DataItemVar;

DataItemVar* hashArrayVar[SIZEVAR];
DataItemVar* dummyItemVar = NULL;
DataItemVar* itemVar;

//function to get the hash index.
int hashCodeVar(char *key) {
  int hash, i;
  for(hash = i = 0; i < SIZEVAR; ++i)
  {
      hash += key[i];
      hash += (hash << 10);
      hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return (hash + SIZEVAR)%SIZEVAR;
}

//function to look for the element in hashmap.
DataItemVar* search_var (char* key){
    //getting the hash index:
    int hashIndex = hashCodeVar(key);

    printf("The key is %s and the hashindex is %d\n", key, hashIndex);
    //moving in the array until an empty index is found.
    while(hashArrayVar[hashIndex] != NULL){
        printf("The key is %s and the hashindex is %d and the current key is %s\n", key, hashIndex, hashArrayVar[hashIndex]->key);
        //if this is the correct cell.
        if(hashArrayVar[hashIndex]->key == key){
            return hashArrayVar[hashIndex];
        }
        //else move to next cell.
        hashIndex++;
        hashIndex %= SIZEVAR;
    }

    assert(hashArrayVar[hashIndex] != NULL && "ERROR: Element not found in hashmap.\n");
    exit(1);
    return NULL;
}

//function to insert into the hashmap.
void insert_var(char* key, size_t data){
    DataItemVar* itemVar = (DataItemVar*)malloc(sizeof(DataItemVar));
    itemVar->data = data;
    itemVar->key = key;

    //getting the hashindex.
    int hashIndex = hashCodeVar(key);
    printf("ye hi print hua\n");
    //printf("%d\n", hashIndex);

    //handling collision by finding the next available position.
    while(hashArrayVar[hashIndex] != NULL/* && hashArrayVar[hashIndex] != -1*/){
        //moving to the next cell.
        hashIndex++;

        //keeping within the size.
        hashIndex %= SIZEVAR;
    }
    
    //inserting the element.
    hashArrayVar[hashIndex] = itemVar;
}

//function to handle the deletion of the element;
DataItemVar* delete_var (DataItemVar* itemVar){
    char* key = itemVar->key;
    
    //getting the index.
    int hashIndex = hashCodeVar(key);

    //moving through the array.
    while(hashArrayVar[hashIndex] != NULL){
        if(hashArrayVar[hashIndex]->key == key){
            DataItemVar* temp = hashArrayVar[hashIndex];
            hashArrayVar[hashIndex] = dummyItemVar;
            return temp;
        }
        hashIndex++;
        hashIndex %= SIZEVAR;
    }
    return NULL;
}

//displaying the entire hashmap.
void display_vars(){
    for(int i = 0; i < SIZEVAR; i++){
        if(hashArrayVar[i] != NULL){
            printf("(%s, %zu)--> ", hashArrayVar[i]->key, hashArrayVar[i]->data);
        }else{
            printf("(~, ~)--> ");
        }
    }
    printf("X\n");
}