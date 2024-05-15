#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
#include "lexerf.h"

int main(){
    FILE* file;
    file = fopen("test.did", "r");
    Token* tokens = lexer(file);
}