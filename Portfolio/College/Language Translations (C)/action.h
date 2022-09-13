#ifndef ACTION_H
#define ACTION_H

//Checks to see if an ID exists in the symbol table, and initializes it in the output file if it doesn't.
void check_id(char* id, FILE** outfile, FILE** tempfile);

//Prints statements to the temp file
void generate(char* string, FILE** tempfile);

//Generates semicolon at end of assign statement
void assign(FILE** tempfile);

//Adds a symbol to the symbol table
void enter(char* symbol);

//Checks if a symbol exists in the symbol table
int lookup(char* symbol);

//Start action routine that writes current date and time to the outfile, as well as header includes and the start of main()
void start(FILE** outfile);

//Finish action routine that writes the return value, closing bracket, and if the program compiled without errors to the temp file.
//The contents of the temp file then get concatenated to the outfile to complete generation of c script.
void finish(FILE** outfile, FILE** tempfile, int errors);

//generates operator in tempfile
void process_op(char* op, FILE** tempfile);

//generates literal in tempfile
void process_literal(char* int_lit, FILE** tempfile);

//checks id in tempfile and generates it
void process_id(char* id, FILE** outfile, FILE** tempfile);

//generates start and end of scanf() statement
void read_id(FILE** tempfile, int start);

//generates start and end of printf() statement
void write_expr(FILE** tempfile, int start);

//generates start and end of if() statement
void if_expr(FILE** tempfile, int start);

//generates beginning of else statement
void else_expr(FILE** tempfile);

//generates the body of either the if, else, or while loop with brackets
void body_cont(FILE** tempfile, int start);

//generates start and end of while() statement
void while_expr(FILE** tempfile, int start);


#endif
