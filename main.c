#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "11c.h"





int main(int argc, char *argv[]){

    if(argc != 2){
        fprintf(stderr, "the number of argument is incorrect.\n");
        return 1;
    }



    user_input = argv[1];
    token = tokenize(argv[1]);
    Node *node = expr();



    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");


    gen(node);


    printf("  pop rax\n");
    printf("  ret\n");

    return 0;

}
