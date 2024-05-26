#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "lexerf.h"

typedef struct Node {
    char* value;
    TokenType type;
    struct Node *left;
    struct Node *right; 
} Node;

//function to print out the tree.
void print_tree(Node* node, int indent, char* identifier){
    if(node == NULL){
        return;
    }
    for(int i = 0; i < indent; i++){
        printf("\t");
    }
    printf("%s -> ", identifier);
    printf("Value: %s\n", node->value);
    print_tree(node->left, indent + 1, "left");
    print_tree(node->right, indent + 1, "right");
}

//function to initialise nodes and allocate required memory.
Node* init_node(Node* node, char* value, TokenType type){
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

//function to print errors.
void print_error(char* error_type){
    printf("ERROR: %s!\n", error_type);
    exit(1);
}

//parser function to generate a tree from the tokens.
Node* parser(Token* tokens){
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

        //tree builiding logic.
        switch(current_token->type){
            printf("TOKEN VALUE: ");
            //support for an keyword syscalls.
            case KEYWORD:
                printf("%s\n", current_token->value);
                //support for an exit syscall.
                if(!strcmp(current_token->value, "EXIT")){
                    Node* exit_node = malloc(sizeof(Node));
                    exit_node = init_node(exit_node, current_token->value, KEYWORD);
                    current->right = exit_node;//* root->right??
                    current = exit_node;
                    current_token++;
                    if(current_token->type == END_OF_TOKENS){
                        print_error("Invalid Syntax on OPEN.");
                    }
                    if(!strcmp(current_token->value, "(") && current_token->type == SEPERATOR){
                        //Node to handle open parenthesis.
                        Node* open_paren_node = malloc(sizeof(Node));
                        open_paren_node = init_node(open_paren_node, current_token->value, SEPERATOR);
                        current->left = open_paren_node;
                        current_token++;
                        if(current_token->type == END_OF_TOKENS){
                            print_error("Invalid Syntax on INT.");
                        }
                        if(current_token->type == INT){
                            //Node to handle the expression within the parenthesis.
                            Node* expr_node = malloc(sizeof(Node));
                            expr_node = init_node(expr_node, current_token->value, INT);
                            current->left->left = expr_node;
                            current_token++;
                            if(current_token->type == END_OF_TOKENS){
                                print_error("Invalid Syntax on CLOSE.");
                            }
                            if(!strcmp(current_token->value, ")") && current_token->type == SEPERATOR){
                                //Node to handle close parenthesis.
                                Node* close_paren_node = malloc(sizeof(Node));
                                close_paren_node = init_node(close_paren_node, current_token->value, SEPERATOR);
                                current->left->right = close_paren_node;
                                current_token++;
                                
                                if(current_token->type == END_OF_TOKENS){
                                    print_error("Invalid Syntax on SEMI.");
                                }
                                if(!strcmp(current_token->value, ";") && current_token->type == SEPERATOR){
                                    //Node to handle semicolons.
                                    Node* semi_node = malloc(sizeof(Node));
                                    semi_node = init_node(semi_node, current_token->value, SEPERATOR);
                                    current->right = semi_node;
                                    printf("EXIT code detected!\n");//*
                                    break; 
                                }else{
                                    print_error("Invalid Syntax on SEMI.");
                                }
                            }else{
                                print_error("Invalid Syntax on CLOSE.");
                            }
                        }else{
                            print_error("Invalid Syntax on INT.");
                        }
                    }else{
                        print_error("Invalid Syntax on OPEN.");
                    }
                }
                //EXIT support over.
                break;
                //KEYWORD support over.

            case SEPERATOR:
                //*
                break;

            case INT:
                //*
                break;

            case BEGINNING:
                //*
                break;

            case END_OF_TOKENS:
                //*
                break;
        }
        current_token++;
    }
    print_tree(root, 0, "root");
    return root;
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
    Node* t = parser(tokens);
    print_tree(t, 0, "root");
    return 0;
}
*/