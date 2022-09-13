#ifndef FILE_UTIL
#define FILE_UTIL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "scanner.h"

int start_up(); // Start function for opening files
void ExtensionAppend(char *filename,int count); //Appends the necessary extension to a filename as needed
void remove_ext(char *input_file,char *output_file,int backup_file); //Removes an extension from a filename as needed
void copy_files(char *filein, char *fileout); //Copies files from an input file to a specified output file 
int FileCheck(char *filename); //Checks to see if a file exists, returns -1 if it does not, 0 if it does
int ValidateOut(char *outfile, char *infile); //Validates the existance of the outfile. If one exists, provide user with options to terminate, re-enter, or overwrite
int ValidateIn(char *infile); //Validates the existance of the infile. If one does not exist, reprompt for one. If nothing is entered, terminate the program.
void BackupFile(char* outpfile); //Generate a backup file from an output file
FILE* ListFile(char* outpfile); //Generate a listing file from an output file
FILE* TempFile(); //Generate a temporary file from an output file (contains commented out code for removal of the file)
FILE* open_file(char* file_name, char* flag);
void close_files(FILE** infile, FILE** outfile, FILE** listfile, FILE** tempfile);
void scanfile(int opened , FILE** infile,FILE** outfile, FILE** listfile );
#endif
