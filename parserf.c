#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "lexerf.h"

typedef enum {
    INT_LIT,
    STATEMENT, 
    EXTRA, 
    BEGINNING,
} NodeTypes;

typedef struct Node {
    char* value;
    NodeTypes type;
    struct Node *right;
    struct Node *left; 
} Node;

void print_tree(Node* node, int indent, char* identifier){
    if(node == NULL){
        return;
    }
    for(int i = 0; i < indent; i++){
        printf(" ");
    }
    printf("%s -> ", identifier);
    printf("Value: %s\n", node->value);
    print_tree(node->left, indent + 1, "left");
    print_tree(node->right, indent + 1, "right");
}

Node* init_node(Node* node, char* value, NodeTypes type){
    node = malloc(sizeof(Node));
    node->value = malloc(sizeof(char)*16);//*
    node->type = type;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}
//in a toy example:
// for the following code:
// exit(12);
// the parser aims to construct the following tree.
//      program
//          \.
//          exit
//          /   \. 
//         (     ;
//        /  \.
//      12    )
Token* parser(Token* tokens){
    Token* current_token = &tokens[0];
    Node* root = malloc(sizeof(Node));
    //Node* left = malloc(sizeof(Node));//*
    //Node* right = malloc(sizeof(Node));//*
    root = init_node(root, "PROGRAM", BEGINNING);

    Node* current = root;
    while(current_token->type != END_OF_TOKENS){
        if(current == NULL){
            break;
        }
        if(current == root){
            //.
        }
        if(current_token->type == KEYWORD && /***/!strcmp(current_token->value, "EXIT")){
            //Node to handle the exit statements.
            Node* exit_node = malloc(sizeof(Node));
            exit_node = init_node(exit_node, current_token->value, STATEMENT);
            current->right = exit_node;//* current->right.
            current = exit_node;
            current_token++;
            if(current_token->type != SEPERATOR){
                printf("ERROR\n");
                exit(1);
            }

            //Node to handle open parenthesis.
            Node* open_paren_node = malloc(sizeof(Node));
            open_paren_node = init_node(open_paren_node, current_token->value, EXTRA);
            current->left = open_paren_node;
            current_token++;

            //Node to handle the expression within the parenthesis.
            Node* expr_node = malloc(sizeof(Node));
            expr_node = init_node(expr_node, current_token->value, INT_LIT);
            current->left->left = expr_node;
            current_token++;

            //Node to handle close parenthesis.
            Node* close_paren_node = malloc(sizeof(Node));
            close_paren_node = init_node(close_paren_node, current_token->value, EXTRA);
            current->left->right = close_paren_node;
            current_token++;

            //Node to handle semicolons.
            Node* semi_node = malloc(sizeof(Node));
            semi_node = init_node(semi_node, current_token->value, EXTRA);
            current->right = semi_node;

            printf("Code exit detected\n");
            break;
        }
        current_token++;
    }
    print_tree(root, 0, "root");
    return current_token;
}

/*
int main(){
    FILE* file = fopen("test.did", "r");
    Token* tokens = lexer(file);
    int token_index = 0;
    printf("Lexing done!\n\n");
    while(tokens[token_index].type != END_OF_TOKENS){
        //printf("TOKEN VALUE: %s\n", tokens[token_index].value);
        //printf("TOKEN TYPE: %d\n", tokens[token_index++].type);
        print_token(tokens[token_index++]);
    }
    print_token(tokens[token_index]);

    printf("Parsing start\n");
    Token* t = parser(tokens);
    return 0;
}
*/