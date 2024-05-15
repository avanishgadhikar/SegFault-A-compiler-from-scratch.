#ifndef LEXER_H
#define LEXER_H

typedef enum {
    INT,
    KEYWORD,
    SEPERATOR,
    END_OF_TOKENS,
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

void print_token(Token token);
Token* generate_number(char current, FILE* file);
Token* generate_keyword(char current, FILE* file);
Token* lexer(FILE* file);

#endif