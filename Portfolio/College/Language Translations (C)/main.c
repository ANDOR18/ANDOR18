/*
* Compiler - Code Generator phase
* Kevin Andor (AND3256@calu.edu), Luke Tingley (TIN2903@calu.edu), Robert Junk (JUN1219@calu.edu)
* CSC460 Group 3
*/

#include "file_util.h"
#include "scanner.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
	int CHAR_SIZE = 20;
	char *infile_name; //Infile name
	char *outfile_name; //Outfile name
	FILE* infile; //Infile
	FILE* outfile; //Outfile
	FILE* listfile; //Outfile
	FILE* tempfile; //Tempfile
	infile_name = (char *)malloc(CHAR_SIZE * sizeof(char));
	outfile_name = (char *)malloc(CHAR_SIZE * sizeof(char));
	int start = 0;
	
	start = start_up(infile_name, outfile_name, &infile, &outfile, &listfile, argc, argv, &tempfile);
	system_goal(start, &infile, &outfile, &listfile, &tempfile);
	close_files(&infile, &outfile, &listfile, &tempfile);
	
	return 0;
}




