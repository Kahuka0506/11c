#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "11c.h"


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













bool consume(char *op){
    if(token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len)) return false;
    token = token->next;
    return true;
}



void expect(char *op){
    if(token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len)) {
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





Token *new_token(TokenKind kind, Token *cur, char *str, int len){
    Token *tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str = str;
    tok->len = len;

    cur->next = tok;
    return tok;
}


bool startswith(char *p, char *q){
    return memcmp(p, q, strlen(q)) == 0;
}


Token *tokenize(){
    char *p = user_input;

    Token head;
    head.next = NULL;
    Token *cur = &head;

    while (*p) {
        if(isspace(*p)){p++; continue;}

        if('a' <= *p && *p <= 'z'){
            cur = new_token(TK_IDENT, cur, p++, 1);
            cur->len = 1;
            continue;
        }

        if(startswith(p, "==") || startswith(p, "!=") || startswith(p, "<=") || startswith(p, ">=")){
            cur = new_token(TK_RESERVED, cur, p, 2);
            p += 2;
            continue;
        }

        if(strchr("+-*/()<>", *p)){
            cur = new_token(TK_RESERVED, cur, p++, 1);
            continue;
        }


        if(isdigit(*p)){
            cur = new_token(TK_NUM, cur, p, 0);
            char *q = p;
            cur->val = strtol(p, &p, 10);
            cur->len = p - q;
            continue;
        }


        //error("tokenize error");
        error_at(p, "tokenize error");
    }

    new_token(TK_EOF, cur, p, 0);
    return head.next;
}
