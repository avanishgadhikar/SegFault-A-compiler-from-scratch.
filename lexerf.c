#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 

//enumerating all types of tokens to be handled.
typedef enum {
    INT,
    KEYWORD,
    SEPERATOR,
    END_OF_TOKENS,
} TokenType;

//struct to store values an tokens.
typedef struct {
    TokenType type;
    char *value;
} Token;

void print_token(Token token){
    printf("TOKEN TYPE: ");
    if(token.type == INT){
        printf("INT\n");
    }
    if(token.type == KEYWORD){
        printf("KEYWORD\n");
    }
    if(token.type == SEPERATOR){
        printf("SEPERATOR\n");
    }
    if(token.type == END_OF_TOKENS){
        printf("END_OF_TOKENS\n");
    }
    printf("TOKEN VALUE: '%s'\n", token.value);
}

//function to identify if the token is a number(INT) and return the value of the number.
Token* generate_number(char current, FILE* file){
    Token* token = malloc(sizeof(Token));
    token->type = INT;
    char *value = malloc(sizeof(char)*8);
    int value_index = 0;
    while(isdigit(current) && current != EOF){
        value[value_index++] = current;
        current = fgetc(file);
    }
    value[value_index] = '\0';
    fseek(file, -1, SEEK_CUR);
    token->value = value;
    return token;
}

//function to identify and return if a token is a keyword(KEYWORD) and return the type of keyword.
Token* generate_keyword(char current, FILE* file){
    Token* token = malloc(sizeof(Token));
    char* keyword = malloc(sizeof(char)*16);
    int keyword_index = 0;
    while(isalpha(current) && current != EOF){
        keyword[keyword_index++] = current;
        current = fgetc(file);
    }
    keyword[keyword_index] = '\0';
    fseek(file, -1, SEEK_CUR);
    //further keyword support can be added here.
    //Currently handles exit.
    if(!strcmp(keyword, "exit")){
        token->type = KEYWORD;
        token->value ="EXIT";
    }
    return token;
}

//function to generate a token if a seperator is found.
Token* generate_seperator(char current){
    Token* token = malloc(sizeof(Token));
    token->value = malloc(sizeof(char)*2);
    token->value[0] = current;
    token->value[1] = '\0';
    token->type = SEPERATOR;
    return token;
}



size_t tokens_index;

Token* lexer(FILE* file){
    char current;
    current = fgetc(file);
    Token* tokens = malloc(sizeof(Token)*1024);
    tokens_index = 0;
    while(current != EOF){
        Token* token = malloc(sizeof(Token));
        if(current == '(' || current == ';' || current == ')'){
            token = generate_seperator(current);
            printf("TOKEN VALUE: %s\n", token->value);
            printf("TOKEN TYPE: %d\n", token->type);
            tokens[tokens_index++] = *token;
        }else if(isdigit(current)){
            token = generate_number(current, file);
            printf("TOKEN VALUE: %s\n", token->value);
            printf("TOKEN TYPE: %d\n", token->type);
            tokens[tokens_index++] = *token;
        }else if(isalpha(current)){
            token = generate_keyword(current, file);
            printf("TOKEN VALUE: %s\n", token->value);
            printf("TOKEN TYPE: %d\n", token->type);
            tokens[tokens_index++] = *token;
        }
        current = fgetc(file);
        free(token);
    }
    tokens[tokens_index].value = '\0';
    tokens[tokens_index].type = END_OF_TOKENS;
    return tokens;
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
    return 0;
}*/
