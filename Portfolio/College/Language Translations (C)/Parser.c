#include "scanner.h"
#include "file_util.h"
#include "Parser.h"
#include "action.h"

//Parse Functions
char* stmt_string;
int sntx_err = 0;
int lex_err = 0;


//Performs a destructive scan for the next token and compares the input with what was expected
char* Match(struct Stack* pstack, token expected, FILE** infile, FILE** outfile, FILE** listfile, int check_statement)
{
	token input; // token from input file
	char* tok_buffer; //Token buffer
	char tok_string[15];
	printf("  ");
	input = scanner(1, &tok_buffer, &infile,&listfile);	
	strcpy(tok_string,token_identify(tok_string,expected));
	while(input==-1)
	{
		printf("  ");
		input = scanner(1, &tok_buffer, &infile,&listfile);
	}
	
	push(pstack, input);
	if(peek(pstack)==expected)
	{
		printf("  ");
		pop(pstack);
	}
	
	else if (peek(pstack) == ERROR)
	{
		lex_err++;
	}
	else
	{
		sntx_err++;
	}
	
	if(input == SCANEOF)
	{
		tok_buffer = "EOF";
	}
	
	strcat(stmt_string, tok_buffer);
	printf("Expected token: %s			Actual token: %s\n", tok_string, tok_buffer);
	
	if(check_statement == 1)
	{
		printf("\nStatement: %s\n\n", stmt_string);
		stmt_string = strdup("");
	}
	
	return tok_buffer;
	
}


//does a non-destructive scan for the next token
token Next_token(FILE** infile,FILE** listfile)
{
	token input; // token from input file
	char* tok_buffer; //Token buffer
	printf("  ");
	input = scanner(0, &tok_buffer, &infile,&listfile);
	int count;
	while(input==-1)
	{
		printf("  ");
		input = scanner(0, &tok_buffer, &infile,&listfile);
	}
	return input;
}

//Stack Functions
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

void push(struct Stack* stack, token item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

int peek(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}

//Grammar Functions
int system_goal(int opened, FILE** infile, FILE** outfile, FILE** listfile, FILE** tempfile)
{
	fpos_t end_list;
	int line_counter = 1;
	token tok; // tok of type token
	char* tok_buffer; //Token buffer
	int count = 0;
	char c;
	struct Stack* pstack = createStack(10000);
	stmt_string = (char *)malloc(200 * sizeof(char));
	stmt_string = strdup("");
	
	if(opened != 1)
	{
		program(pstack, infile, outfile,listfile, tempfile); //Continues chain of grammar checking functions
		Match(pstack, SCANEOF, infile, outfile,listfile, 1); //Matches the EOF token
//		fgetpos(*listfile, &end_list);
		fprintf(*listfile, "\n\n");
		printf("   ");
/*		c=fgetc(*listfile);
		while(c != EOF)
		{

			if(c == '\n')
			{
				if(line_counter == 2)
				{
					line_counter--;
					fgetpos(*listfile, &end_list);
				}
				else
					line_counter++;
			}
			
			c=fgetc(*listfile);
		}*/
			
	//	fsetpos(*listfile, &end_list);
		
		if(!isEmpty(pstack)) //If parse stack still has items, compilation failed
		{
			fprintf(*listfile, "\nInput file compilation failed\n");
			finish(outfile, tempfile, 1);
		}
		else
		{
			fprintf(*listfile, "\nInput file compiled without errors\n");
			finish(outfile, tempfile, 0);
		}
		
		fprintf(*listfile, "Total number of lexical errors: %d		Total number of syntax errors: %d", lex_err, sntx_err);
		

//		printf("%c",c);
	}
	
	else
	{
		printf("Files did not open.");
	}
}

int program(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	start(outfile);
	Match(pstack, BEGIN, infile, outfile,listfile, 1);
	stmt_list(pstack, infile, outfile,listfile, tempfile);
	Match(pstack, END, infile, outfile,listfile, 1);
}

int stmt_list(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	statement(pstack, infile, outfile,listfile, tempfile);
	next = Next_token(infile,listfile);

	if(((int)next >= 2 && (int)next <= 4) || next == ID || next == WHILE)
	{
		stmt_list(pstack, infile, outfile,listfile, tempfile);	
	}
}

int statement(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	
	token next;
	next = Next_token(infile,listfile);
	switch(next){
		case ID: 
			ident(pstack, infile, outfile,listfile, tempfile);
			Match(pstack, ASSIGNOP, infile, outfile,listfile,0);
			generate(" = ", tempfile);
			expression(pstack, infile, outfile,listfile, tempfile);
			assign(tempfile);
			Match(pstack, SEMICOLON, infile, outfile,listfile,1);
			break;
		case READ:
			Match(pstack, READ, infile, outfile,listfile,0);
			Match(pstack, LPAREN, infile, outfile,listfile,0);
			id_list(pstack, infile, outfile,listfile, tempfile);
			Match(pstack, RPAREN, infile, outfile,listfile,0);
			Match(pstack, SEMICOLON, infile, outfile,listfile,1);
			break;
		case WRITE:
			Match(pstack, WRITE, infile, outfile,listfile,0);
			Match(pstack, LPAREN, infile, outfile,listfile,0);
			expr_list(pstack, infile, outfile,listfile, tempfile);
			Match(pstack, RPAREN, infile, outfile,listfile,0);
			Match(pstack, SEMICOLON, infile, outfile,listfile,1);
			break;
		case IF:
			Match(pstack, IF, infile, outfile,listfile,0);
			Match(pstack, LPAREN, infile, outfile,listfile,0);
			if_expr(tempfile, 1);
			condition(pstack, infile, outfile,listfile, tempfile);
			Match(pstack, RPAREN, infile, outfile,listfile,1);
			if_expr(tempfile, 0);
			Match(pstack, THEN, infile, outfile,listfile,1);
			body_cont(tempfile, 1);
			stmt_list(pstack, infile, outfile,listfile, tempfile);
			IFTail(pstack, infile, outfile,listfile, tempfile);
			break;
		case WHILE:
			Match(pstack, WHILE, infile, outfile,listfile,0);
			Match(pstack, LPAREN, infile, outfile,listfile,0);
			while_expr(tempfile, 1);
			condition(pstack, infile, outfile,listfile, tempfile);
			Match(pstack, RPAREN, infile, outfile,listfile,1);
			while_expr(tempfile, 0);
			body_cont(tempfile, 1);
			stmt_list(pstack, infile, outfile,listfile, tempfile);
			Match(pstack, ENDWHILE, infile, outfile,listfile,1);
			body_cont(tempfile, 0);
			break;
	}
}

int IFTail(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	next = Next_token(infile,listfile);

	if(next == ELSE)
	{
		Match(pstack, ELSE, infile, outfile,listfile,1);
		body_cont(tempfile, 0);
		else_expr(tempfile);
		body_cont(tempfile, 1);
		stmt_list(pstack, infile, outfile,listfile, tempfile);
		Match(pstack, ENDIF, infile, outfile,listfile,1);
		body_cont(tempfile, 0);
	}
	else if(next == ENDIF)
	{
		Match(pstack, ENDIF, infile, outfile,listfile,1);
		body_cont(tempfile, 0);
	}
}

int id_list(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	read_id(tempfile, 1);
	//printf("hit");
	ident(pstack, infile, outfile,listfile, tempfile);
	read_id(tempfile, 0);
	next = Next_token(infile,listfile);
	if(next == COMMA)
	{	
		Match(pstack, COMMA, infile, outfile,listfile,0);
		id_list(pstack, infile, outfile,listfile, tempfile);
	}
}

int expr_list(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	write_expr(tempfile, 1);
	expression(pstack, infile, outfile,listfile, tempfile);
	write_expr(tempfile, 0);

	next = Next_token(infile,listfile);
	if(next == COMMA)
	{
		Match(pstack, COMMA, infile, outfile,listfile,0);
		expr_list(pstack, infile, outfile,listfile, tempfile);
	}
}

int expression(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	term(pstack, infile, outfile,listfile, tempfile);
	next = Next_token(infile,listfile);
	if(next == PLUSOP||next == MINUSOP)
	{
		add_op(pstack, infile, outfile,listfile, tempfile);
		expression(pstack, infile, outfile,listfile, tempfile);
		//#gen_infix
	}
}

int term(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{	
	token next;
	factor(pstack, infile, outfile,listfile, tempfile);
	next = Next_token(infile,listfile);
	if(next == MULTOP||next == DIVOP)
	{
		mult_op(pstack, infile, outfile,listfile, tempfile);
		term(pstack, infile, outfile,listfile, tempfile);
	}
}

int factor(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	char* int_lit;
	token next;
	next = Next_token(infile,listfile);
	switch(next)
	{
		case INTLITERAL:
			int_lit = Match(pstack, INTLITERAL, infile, outfile,listfile,0);
			process_literal(int_lit, tempfile);
			break;
			
		case ID:
			ident(pstack, infile, outfile,listfile, tempfile);
			break;
			
		case MINUSOP:
			Match(pstack, MINUSOP, infile, outfile,listfile,0);
			process_op(" -", tempfile);
			factor(pstack, infile, outfile,listfile, tempfile);
			break;
			
		case LPAREN:
			Match(pstack, LPAREN, infile, outfile,listfile,0);
			expression(pstack, infile, outfile,listfile, tempfile);
			Match(pstack, RPAREN, infile, outfile,listfile,0);
			break;
	}
}


int condition(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	addition(pstack, infile, outfile,listfile, tempfile);
	next = Next_token(infile,listfile);
	if((int)next >= 25 && (int)next <= 30)
	{
		rel_op(pstack, infile, outfile,listfile, tempfile);
		addition(pstack, infile, outfile,listfile, tempfile);
		//#gen_infix
	}
	
}

int addition(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	multiplication(pstack, infile, outfile,listfile, tempfile);
	next = Next_token(infile,listfile);
	if(next == PLUSOP||next == MINUSOP)
	{
		add_op(pstack, infile, outfile,listfile, tempfile);
		multiplication(pstack, infile, outfile,listfile, tempfile);
		//#gen_infix
	}
	
}

int multiplication(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	unary(pstack, infile, outfile,listfile, tempfile);
	next = Next_token(infile,listfile);
	if(next == MULTOP||next == DIVOP)
	{
		mult_op(pstack, infile, outfile,listfile, tempfile);
		unary(pstack, infile, outfile,listfile, tempfile);
		//#gen_infix
	}
	
}

int unary(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	next = Next_token(infile,listfile);
	switch(next)
	{
		case NOTOP:
			Match(pstack, NOTOP, infile, outfile,listfile,0);
			process_op(" !", tempfile);
			unary(pstack, infile, outfile,listfile, tempfile);
			break;
			
		case MINUSOP:
			Match(pstack, MINUSOP, infile, outfile,listfile,0);
			process_op(" -", tempfile);
			unary(pstack, infile, outfile,listfile, tempfile);
			break;
			
		default:
			lprimary(pstack, infile, outfile,listfile, tempfile);
			break;
	}	
}

int lprimary(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	char* int_lit;
	next = Next_token(infile,listfile);
	switch(next)
	{
		case INTLITERAL:
			int_lit = Match(pstack, INTLITERAL, infile, outfile,listfile,0);
			process_literal(int_lit, tempfile);
			break;
		case ID:
			ident(pstack, infile, outfile,listfile, tempfile);
			break;
		case FALSEOP:
			Match(pstack, FALSEOP, infile, outfile,listfile,0);
			process_op(" 0 ", tempfile);
			break;
		case TRUEOP:
			Match(pstack, TRUEOP, infile, outfile,listfile,0);
			process_op(" 1 ", tempfile);
			break;
		case NULLOP:
			Match(pstack, NULLOP, infile, outfile,listfile,0);
			process_op(" NULL ", tempfile);
			break;
		case LPAREN:
			Match(pstack, LPAREN, infile, outfile,listfile,0);
			condition(pstack, infile, outfile,listfile, tempfile);
			Match(pstack, RPAREN, infile, outfile,listfile,0);
			break;
	}
}

int rel_op(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	next = Next_token(infile,listfile);
	switch(next)
	{
		case LESSOP:
			Match(pstack, LESSOP, infile, outfile,listfile,0);
			process_op(" < ", tempfile);
			break;
				
		case LESSEQUALOP:
			Match(pstack, LESSEQUALOP, infile, outfile,listfile,0);
			process_op(" <= ", tempfile);
			break;
			
		case GREATEROP:
			Match(pstack, GREATEROP, infile, outfile,listfile,0);
			process_op(" > ", tempfile);
			break;
			
		case GREATEREQUALOP:
			Match(pstack, GREATEREQUALOP, infile, outfile,listfile,0);
			process_op(" >= ", tempfile);
			break;
				
		case EQUALOP:
			Match(pstack, EQUALOP, infile, outfile,listfile,0);
			process_op(" == ", tempfile);
			break;
			
		case NOTEQUALOP:
			Match(pstack, NOTEQUALOP, infile, outfile,listfile,0);
			process_op(" != ", tempfile);
			break;
	}
}

int add_op(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	next = Next_token(infile,listfile);
	if(next == PLUSOP)
	{
		Match(pstack, PLUSOP, infile, outfile,listfile,0);
		process_op(" + ", tempfile);	
	}
	
	else if(next == MINUSOP)
	{
		Match(pstack, MINUSOP, infile, outfile,listfile,0);
		process_op(" - ", tempfile);
	}
	
}

int mult_op(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	token next;
	next = Next_token(infile,listfile);
	if(next == MULTOP)
	{
		Match(pstack, MULTOP, infile, outfile,listfile,0);
		process_op(" * ", tempfile);
	}
	
	else if(next == DIVOP)
	{
		Match(pstack, DIVOP, infile, outfile,listfile,0);
		process_op(" / ", tempfile);
	}
}

int ident(struct Stack* pstack, FILE** infile, FILE** outfile,FILE** listfile, FILE** tempfile)
{
	char* id;
	id = Match(pstack, ID, infile, outfile,listfile,0);
	process_id(id, outfile, tempfile);
}










