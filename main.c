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
    //token = tokenize(argv[1]);
    //Node *node = expr();
    tokenize();
    program();


    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");

    printf("  push rbp\n");
    printf("  mov rbp, rsp\n");
    printf("  sub rsp, 208\n");

    for (int i = 0; code[i]; i++) {
        gen(code[i]);
    }


    printf("  mov rsp, rbp\n");
    printf("  pop rax\n");
    printf("  ret\n");

    return 0;

}
