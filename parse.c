#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "11c.h"

Node *assign(){
    Node *node = equality();
    if(consume("==")){
        node = new_node(ND_ASSIGN, node, assign());
    }
    return node;
}


Node *expr(){
    return assign();
}

Node *stmt(){
    Node *node = expr();
    expect(";");
    return node;
}

void program(){
    int i = 0;
    while (!at_eof()) {
        code[i++] = stmt();
    }
    code[i] = NULL;
}

Node *new_node(NodeKind kind){
    Node *node = calloc(1, sizeof(Node));
    node->kind = kind;
    return node;
}

Node *new_binary(NodeKind kind, Node *lhs, Node *rhs){
    Node *node = new_node(kind);
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node *new_num(int val){
    Node *node = new_node(ND_NUM);
    node->val = val;
    return node;
}



Node *equality(){
    Node *node = relational();

    for(;;){
        if(consume("==")){
            node = new_binary(ND_EQ, node, relational());
        }else if(consume("!=")){
            node = new_binary(ND_NE, node, relational());
        }else{
            return node;
        }
    }
}

Node *relational(){
    Node *node = add();

    for(;;){
        if(consume("<")){
            node = new_binary(ND_LT, node, add());
        }else if(consume("<=")){
            node = new_binary(ND_LE, node, add());
        }else if(consume(">")){
            node = new_binary(ND_LT, add(), node);
        }else if(consume(">=")){
            node = new_binary(ND_LE, add(), node);
        }else {
            return node;
        }
    }
}

Node *add(){
    Node *node = mul();

    for(;;){
        if(consume("+")){
            node = new_binary(ND_ADD, node, mul());
        }else if(consume("-")){
            node = new_binary(ND_SUB, node, mul());
        }else{
            return node;
        }
    }
}

Node *mul(){
    Node *node = unary();

    for(;;){
        if(consume("*")){
            node = new_binary(ND_MUL, node, unary());
        }else if(consume("/")){
            node = new_binary(ND_DIV, node, unary());
        }else{
            return node;
        }
    }
}

Node *unary(){
    if(consume("+")){
        return unary();
    }
    if(consume("-")){
        return new_binary(ND_SUB, new_num(0), unary());
    }
    return primary();
}

Node *primary() {

    Token *tok = consume_ident();
    if(tok){
        Node *node = calloc(1, sizeof(Node));
        node->kind = ND_LVAR;
        node->offset = (tok->str[0] - 'a' + 1) * 8;
        return node;
    }

    if(consume("(")){
        Node *node = expr();
        expect(")");
        return node;
    }

    return new_num(expect_number());
}
