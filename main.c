#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
typedef enum {
    SEMI, 
    OPEN_PAREN,
    CLOSE_PAREN,
} TypeSeperator;

typedef enum {
    EXIT, 
}TypeKeyword;

typedef enum {
    INT, 
}TypeLiteral;

typedef struct {
    TypeKeyword type;
}TokenKeyword;

typedef struct {
    TypeSeperator type;
}TokenSeperator;

typedef struct {
    TypeLiteral type;
    char* value;
}TokenLiteral;

TokenLiteral* generate_number(char current, FILE* file){
    TokenLiteral* token = malloc(sizeof(TokenLiteral));
    token->type = INT;
    char* value = malloc(sizeof(char)*8);
    int value_index = 0;
    while(isdigit(current) && current != EOF){
        value[value_index++] = current;
        current = fgetc(file); 
    }
    fseek(file, -1, SEEK_CUR);
    token->value = value;
    return (token);
}

TokenKeyword* generate_keyword(char current, FILE* file){
    TokenKeyword* token = malloc(sizeof(TokenKeyword));
    char *keyword = malloc(sizeof(char) * 8);
    int keyword_index = 0;
    while(isalpha(current) && current != EOF){
        keyword[keyword_index++] = current;
        current = fgetc(file);
    }
    fseek(file, -1, SEEK_CUR);
    if(!strcmp(keyword, "exit")){
        token->type = EXIT;
    }
    return token;
}

void lexer (FILE* file){
    char current = fgetc(file);
    while(current != EOF){
        if(current == ';'){
            printf("FOUND SEMICOLON\n");
        }else if(current == '('){
            printf("FOUND OPEN PAREN\n");
        }else if(current == ')'){
            printf("FOUND CLOSE PAREN\n");
        }else if(isdigit(current)){
            TokenLiteral *test_token = generate_number(current, file);
            printf("TEST TOKEN VALUE: %s\n", test_token->value);
        }else if(isalpha(current)){
            TokenKeyword *test_token = generate_keyword(current, file);
            printf("FOUND TEST TOKEN, KEYWORD:\n");
            if(test_token->type == EXIT){
                printf("KEYWORD: EXIT\n");
            }
            //printf("FOUND CHARACTER: %c\n", current);
        }
        //printf("%c", current);
        current= fgetc(file);
    }
}

int main(){
    FILE* file;
    file = fopen("test.did", "r");
    int length;
    //fseek(file, 0, SEEK_END);
    //length = ftell(file);
    //fseek(file, 0, SEEK_SET);
    lexer(file);
}