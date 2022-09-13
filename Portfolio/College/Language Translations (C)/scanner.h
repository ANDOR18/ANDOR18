#ifndef SCAN_H
#define SCAN_H
#include <ctype.h>
#include "file_util.h"

typedef enum token
{
	BEGIN = 0,
	END = 1,
	READ = 2,
	WRITE = 3,
	IF = 4,
	THEN = 5,
	ELSE = 6,
	ENDIF = 7,
	WHILE = 8,
	ENDWHILE = 9,
	ID = 10,
	INTLITERAL = 11,
	FALSEOP = 12,
	TRUEOP = 13,
	NULLOP = 14,
	LPAREN = 15,
	RPAREN = 16,
	SEMICOLON = 17,
	COMMA = 18,
	ASSIGNOP = 19,
	PLUSOP = 20,
	MINUSOP = 21,
	MULTOP = 22,
	DIVOP = 23,
	NOTOP = 24,
	LESSOP = 25,
	LESSEQUALOP = 26,
	GREATEROP = 27,
	GREATEREQUALOP = 28,
	EQUALOP = 29,
	NOTEQUALOP = 30,
	SCANEOF = 31,
	ERROR = 32
}token;

token scanner(int destructive, char** buffer, FILE*** infile,FILE*** listfile);//, FILE*** outfile, FILE*** listfile); //Main scanning function
token check_reserved(char** buffer); //Returns the token of the string
char* token_identify(char* buffer,token tok); //Identifies the string for the token
void add_char(char** buffer, char character); //Adds a character to the buffer
#endif
