#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h> 

#include "lexerf.h"
#include "parserf.h"

//function to traverse the tree in order.
void traverse_tree(Node* node, int is_left, FILE* file){
    if(node == NULL){
        return;
    }
    //traversing the tree and dealing with individual cases.
    if(!strcmp(node->value, "EXIT")){
        fprintf(file, "  mov rax, 60\n");
    }
    if(!strcmp(node->value, "(") || !strcmp(node->value, ")")){
        //*
    }
    if(node->type == INT){
        fprintf(file, "  mov rdi, %s\n", node->value);
    }
    if(!strcmp(node->value, ";")){
        fprintf(file, "  syscall\n");
    }

    if(is_left){
        //*
    }else{
        //*
    }

    printf("%s \n", node->value);
    traverse_tree(node->left, 1, file);
    traverse_tree(node->right, 0, file);
}

//function to generate the assembly code that traverses the tree and generates assembly file.
int generate_code(Node* root){
    FILE* file = fopen("generated.asm", "w");
    assert(file != NULL && "FILE COULD NOT BE OPENED\n");

    fprintf(file, "section .text\n");
    fprintf(file, "  global _start\n\n");
    fprintf(file, "_start:\n");

    traverse_tree(root, 0, file);
    fclose(file);

    return 0; //* void function maybe?
}