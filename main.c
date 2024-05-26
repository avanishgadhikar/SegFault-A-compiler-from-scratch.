#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>

#include "lexerf.h"
#include "parserf.h"
#include "codegeneratorf.h"

/*
To Run the file:
gcc -c main.c
gcc -c lexerf.c
gcc -c parserf.c
gcc main.o lexerf.o -o demo
./demo
*/

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Error: correct syntax: %s <filename.did>\n", argv[0]);
        exit(1);
    }
    FILE* file;
    file = fopen(argv[1], "r");

    if(!file){
        printf("ERROR: File not found\n");
        exit(1);
    }

    Token* tokens = lexer(file);
    int token_index = 0;
    while(tokens[token_index].type != END_OF_TOKENS){
        print_token(tokens[token_index++]);
    }
    print_token(tokens[token_index]); //to print END OF TOKENS.

    Node* test = parser(tokens);
    printf("TREE:\n");
    //generating an assembly code and running the subsequent file.
    generate_code(test);
    FILE* assembly_file = fopen("generated.asm", "r");
    if(!assembly_file){
        printf("ERROR!\n");
        exit(1);
    }
    //executing the buildasm in the terminal.
    if(system("./buildasm.sh")){
        printf("ERROR\n");
        exit(1);
    }
    return 0;
}