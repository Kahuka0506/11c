
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char *user_input;




//________________________________________________________________

void error(char *format, ...);
void error_at(char *loc, char *format, ...);




//________________________________________________________________

typedef enum{
    TK_RESERVED,    // keyword or punctuators
    TK_IDENT,
    TK_NUM,         // integer literals
    TK_EOF,         //end of file markers
} TokenKind;
typedef struct Token Token;
struct Token{
    TokenKind kind;
    Token *next;
    int val;
    char *str;
    int len;
};
Token *token;


bool consume(char *op);
void expect(char *op);
int expect_number();
bool at_eof();





Token *new_token(TokenKind kind, Token *cur, char *str, int len);
bool startswith(char *p, char *q);
Token *tokenize();







//________________________________________________________________


typedef enum{
    ND_ADD,        // +
    ND_SUB,        // -
    ND_MUL,        // *
    ND_DIV,        // /
    ND_EQ,         // ==
    ND_NE,         // !=
    ND_LT,         // <
    ND_LE,         // <=
    ND_ASSIGN,
    ND_LVAR,
    ND_NUM,        // Integer
} NodeKind;
typedef struct Node Node;
struct Node{
    NodeKind kind;
    Node *lhs;
    Node *rhs;
    int val;
    int offset;
};

Node *code[100];



Node *new_node(NodeKind kind);
Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);
Node *new_num(int val);


Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

void program();


void gen(Node *node);
