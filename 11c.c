#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>





typedef enum{
    TK_RESERVED,
    TK_NUM,
    TK_EOF,
} TokenKind;
typedef struct Token Token;
struct Token{
    TokenKind kind;
    Token *next;
    int val;
    char *str;
};
Token *token;


typedef enum{
    ND_ADD,
    ND_SUB,
    ND_MUL,
    ND_DIV,
    ND_NUM,
} NodeKind;
typedef struct Node Node;
struct Node{
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    int val;
};






char *user_input;


void error(char *format, ...){
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void error_at(char *loc, char *format, ...){
    va_list ap;
    va_start(ap, format);

    int pos = loc - user_input;
    fprintf(stderr, "%s\n", user_input);
    fprintf(stderr, "%*s", pos, "");
    fprintf(stderr, "^ ");
    vfprintf(stderr, format, ap);
    fprintf(stderr, "\n");
    exit(1);
}








bool consume(char op){
    if(token->kind != TK_RESERVED || token->str[0] != op) return false;
    token = token->next;
    return true;
}



void expect(char op){
    if(token->kind != TK_RESERVED || token->str[0] != op) {
        //error("not '%c'", op);
        error_at(token->str, "not '%c'", op);
    }

    token = token->next;
}


int expect_number(){
    if(token->kind != TK_NUM) {
        //error("not number");
        error_at(token->str, "not number");
    }
    int val = token->val;
    token = token->next;
    return val;
}


bool at_eof(){
    return token->kind == TK_EOF;
}





Token *new_token(TokenKind kind, Token *cur, char *str){
    Token *tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str = str;
    cur->next = tok;
    return tok;
}



Token *tokenize(char *p){
    Token head;
    head.next = NULL;
    Token *cur = &head;

    while (*p) {
        if(isspace(*p)){p++; continue;}

        if(*p == '+' || *p == '-'){
            cur = new_token(TK_RESERVED, cur, p);
            p++;
            continue;
        }

        if(isdigit(*p)){
            cur = new_token(TK_NUM, cur, p);
            cur->val = strtol(p, &p, 10);
            continue;
        }


        //error("tokenize error");
        error_at(p, "tokenize error");
    }

    new_token(TK_EOF, cur, p);
    return head.next;
}










int main(int argc, char *argv[]){

    if(argc != 2){
        fprintf(stderr, "the number of argument is incorrect.\n");
        return 1;
    }



    user_input = argv[1];
    token = tokenize(argv[1]);




    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");
    printf("  mov rax, %d\n", expect_number());


    while (!at_eof()) {
        if(consume('+')){
            printf("  add rax, %d\n", expect_number());
            continue;
        }

        expect('-');
        printf("  sub rax, %d\n", expect_number());
    }

    printf("  ret\n");

    return 0;

}
