#include "file_util.h"
#include <time.h>
#include <assert.h>
#define STABLE_LEN 100

char* symbol_table[STABLE_LEN] = {0};


//Checks to see if an ID exists in the symbol table, and initializes it in the output file if it doesn't.
void check_id(char* id, FILE** outfile, FILE** tempfile)
{
	if (lookup(id) == 0)
	{
		enter(id);
		fprintf(*outfile,"int %s;\n", id);
	//	fprintf(*tempfile,"int %s\n", id);
	}
	
	generate(id, tempfile);
	
}

//Prints statements to the temp file
void generate(char* string, FILE** tempfile)
{
	fprintf(*tempfile, "%s", string);
}

//Generates semicolon at end of assign statement
void assign(FILE** tempfile)
{
	generate(";\n", tempfile);
}

//Adds a symbol to the symbol table
void enter(char* symbol)
{
	int i;
	for (i = 0; symbol_table[i]!=0; i++);
	symbol_table[i] = symbol;
}

//Checks if a symbol exists in the symbol table
int lookup(char* symbol)
{
	int i = 0;
	int exists = 0;
	
	while (exists == 0 && symbol_table[i] != 0)
	{
		if (strcmp(symbol, symbol_table[i]) == 0)
		{

			exists = 1;
		}
		i += 1;
	}

	return exists;
}

//Start action routine that writes current date and time to the outfile, as well as header includes and the start of main()
void start(FILE** outfile)
{
	int i;
	for(i = 0; i < 0; i++)
	{
		symbol_table[i] = (char *)malloc(20 * sizeof(char));
	}
	time_t cur_time = time(NULL);
	struct tm *tm = localtime(&cur_time);
	char date_time[64];
    assert(strftime(date_time, sizeof(date_time), "%c", tm));
    
    fprintf(*outfile, "//Current Date and Time:\n");
    fprintf(*outfile, "//%s\n", date_time);
	fprintf(*outfile,"#include <stdio.h>\n");
	fprintf(*outfile,"int main()\n");
	fprintf(*outfile,"{\n");
}


//Finish action routine that writes the return value, closing bracket, and if the program compiled without errors to the temp file.
//The contents of the temp file then get concatenated to the outfile to complete generation of c script.
void finish(FILE** outfile, FILE** tempfile, int errors)
{
	char c;
	fprintf(*tempfile,"\nreturn 0;\n}\n");
	if (errors == 1)
	{
		fprintf(*tempfile, "\n//File compilation failed");
	}
	else
	{
		fprintf(*tempfile, "\n//File compiled without errors");
	}
	
	rewind(*tempfile);
	
	c=fgetc(*tempfile);
//	printf("%c", c);
	while(c != EOF)
	{
		fputc(c, *outfile);
		c=fgetc(*tempfile);
//		printf("%c", c);
	}
	
}

//generates operator in tempfile
void process_op(char* op, FILE** tempfile)
{
	generate(op, tempfile);
}

//generates literal in tempfile
void process_literal(char* int_lit, FILE** tempfile)
{
	generate(int_lit, tempfile);
}

//checks id in tempfile and generates it
void process_id(char* id, FILE** outfile, FILE** tempfile)
{
	check_id(id, outfile, tempfile);
}

//generates start and end of scanf() statement
void read_id(FILE** tempfile, int start)
{
	if(start == 1)
	{
		generate("scanf(\"%d\", &", tempfile);
	}
	else
	{
		generate(" );\n", tempfile);
	}
}

//generates start and end of printf() statement
void write_expr(FILE** tempfile, int start)
{
	if(start == 1)
	{
		generate("printf(\"%d\\n\", ", tempfile);
	}
	else
	{
		generate(" );\n", tempfile);
	}
}

//generates start and end of if() statement
void if_expr(FILE** tempfile, int start)
{
	if(start == 1)
	{
		generate("if( ", tempfile);
	}
	else
	{
		generate(" )\n", tempfile);
	}
}

//generates beginning of else statement
void else_expr(FILE** tempfile)
{
		generate("else", tempfile);
}

//generates the body of either the if, else, or while loop with brackets
void body_cont(FILE** tempfile, int start)
{
	if(start == 1)
	{
		generate("{\n ", tempfile);
	}
	else
	{
		generate("}\n", tempfile);
	}
}

//generates start and end of while() statement
void while_expr(FILE** tempfile, int start)
{
	if(start == 1)
	{
		generate("while( ", tempfile);
	}
	else
	{
		generate(" )\n", tempfile);
	}
}
