#ifndef HASHMAP_VARS_H_
#define HASHMAP_VARS_H_

#include <stdio.h>
#define SIZEVAR 20

typedef struct DataItemVar {
    size_t data;
    char* key;
}DataItemVar;

int hashCodeVar(char* key);
DataItemVar* search_var (char* key);
void insert_var(char* key, size_t data);
DataItemVar* delete_var (DataItemVar* itemVar);
void display_vars();

#endif