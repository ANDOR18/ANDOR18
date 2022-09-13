#ifndef PARSER_H
#define PARSER_H
#include <ctype.h>
#include "file_util.h"

struct Stack {
    int top;
    unsigned capacity;
    token* array;
};

extern char* stmt_string;
char* Match();
token Next_token();
int parser();
int isEmpty();
int isFull();
int peek();
int pop();
void push();
struct Stack* createStack();
int system_goal();
int program();
int stmt_list(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int statement(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int IFTail(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int id_list(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int expr_list(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int expression(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int term(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int factor(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int condition(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int addition(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int multiplication(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int unary(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int lprimary(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int rel_op(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int add_op(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int mult_op(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);
int ident(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile);

#endif
