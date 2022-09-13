#include "file_util.h"		


// start function to begin program
int start_up(char* infile_name, char* outfile_name, FILE** infile, FILE** outfile, FILE** listfile, int argc, char* argv[], FILE** tempfile)
{
	int start = 0;
	int quit = 0;
	int file_chk = 1;
	
	
	fpos_t start_in;
	fpos_t start_out;
	int line_counter = 1;
	char c;

	//starts the check for how many arguments entered
//	printf("program file name: %s\n",argv[0]);

	//If some or none of the parameters are entered
	if(argc < 3){
		
		//If no parameters are entered, take the input file
		if(argc <= 1)
		{
			printf("Please enter a name for the infile: ");
			gets(infile_name);
			quit = ValidateIn(infile_name);
//			printf("Infile: %s\n", infile);
		}
		
		//If there is a parameter entered, take input file from arguments
		else
		{
			infile_name = argv[1];
			quit = ValidateIn(infile_name);
//			printf("Infile: %s\n", infile);
		}
		
		if(quit != 1)
		{
			//Take the output file name and proccess it
			printf("Please enter a name for the outfile: ");
			gets(outfile_name);
			quit = ValidateOut(outfile_name, infile_name);
//			printf("Outfile: %s\n", outfile);			
			//samestring(outfile,tempfile);
		}
	}
	//If both arguments are found, store them
	else
	{
		infile_name = argv[1];
		quit = ValidateIn(infile_name);
		//samestring(infile,tempfile);
		
		if(quit != 1)
		{
			outfile_name = argv[2];
			quit = ValidateOut(outfile_name, infile_name);
		}
	}
		
	
	//Complete the file opening, writing, and closing
	if(quit != 1)
	{
	//	printf("Opening file...");
		*infile = open_file(infile_name, "r");
		*outfile = open_file(outfile_name, "w");
		*listfile = ListFile(outfile_name);
		*tempfile = TempFile();

		fgetpos(*infile, &start_in);
		//fgetpos(*listfile, &start_out);
//		printf("hit");
	
		fprintf(*listfile, "%d. ", line_counter);
		line_counter++;
		c=fgetc(*infile);
//	printf("%c",c);
		while(c != EOF)
		{
			fputc(c, *listfile);
			if( c == '\n')
			{
				fprintf(*listfile, "%d. ", line_counter);
				line_counter++;
			}
			c=fgetc(*infile);
//		printf("%c",c);
		}
	
		fsetpos(*infile, &start_in);
		//fsetpos(*listfile, &start_out);
		return quit;
	}
	
	else
	{
		printf("Compilation terminated...");
		return quit;
	}
}


void ExtensionAppend(char *filename, int count)
{
	/*
	----------------------------------------
	| this function purpose to confirm the |
	| file have an extension and if they   |
	| do not have the correct extension    |
	| the we have to add the approprite    |
	| extension                            |
	----------------------------------------
	*/
	
	int ext_chk = 0;
	int p_loc = 0;
	int i;
	char *extout = ".c";
	char *extin = ".in";
	char *lis = ".lis";
	char *bak = ".bak";
	char *out;
	char *extn;
	
	for (i=0; i<strlen(filename); i++)
	{
		if(filename[i]=='.')
		{
			if(i != (strlen(filename)))
			{
				p_loc = i;
				ext_chk = 1;
			}
		}
	}
	
	//if exit-check is not equal to one add extension to input or output
	if(ext_chk != 1)
	{
		//if the count is 1 then append .in
		if(count == 1)
		{
			extn = extin;
		}
		
		//if the count is 2 then append .out
		if(count == 2)
		{
			extn = extout;
		}
		
		//.lis
		if(count == 3)
		{
			extn = lis;
		}
		
		//.bak
		if(count == 4)
		{
			extn = bak;
		}
		
		//Appends the set extension
		out = malloc(strlen(filename)+strlen(extn)+1);
		strcpy(out,filename);
		strcat(out,extn);
		strcpy(filename,out);
	}
}	

//Validates the input file's existance. If it doesn't reprompt for a valid input file. If nothing is entered, terminate.
int ValidateIn(char *infile)
{
	int file_chk = 1;
	int quit = 0;
	
	while (file_chk != 0 && quit == 0)
	{
		if(strcmp(infile,"") != 0)
		{
			ExtensionAppend(infile, 1);
			file_chk = FileCheck(infile);
			if(file_chk != 0)
			{
				printf("Invalid input file entered, please enter a valid input file: ");
				gets(infile);
			}
		}
							
		else
		{
			quit = 1;
		}
	}
	
	return quit;
}

//Validates the output file's non-existance. If it does exist, give options to re-enter, overwrite, or terminate.
int ValidateOut(char *outfile, char *infile)
{
	int file_chk = 0;
	int str_chk;
	int quit = 0;
	int temp = 0;
	char *selection;
	
	
	while(file_chk == 0 && quit == 0)
	{
		remove_ext(infile,outfile,temp);
		ExtensionAppend(outfile,2);
		//printf("checking %s...", outfile);
		str_chk = strcmp(infile, outfile);
		if(str_chk == 0)
		{
			printf("The output file name entered is the same as the input file. Please enter a different name: ");
			gets(outfile);
		}
		
		else
		{
			file_chk = FileCheck(outfile);
					
			if(file_chk == 0)
			{
				printf("Output file already exists\n");
				printf("Commands:\n n : Re-enter output file \n o : Overwrite output file \n q : Quit Program \n");
				printf("Enter one of the commands: ");
				selection = (char *)malloc(20 * sizeof(char));
				gets(selection);
				if(strcmp(selection,"n") == 0 || strcmp(selection,"N") == 0)
				{
					printf("Please re-enter a name for the outfile: ");
					gets(outfile);
				}
						
				else if(strcmp(selection,"q") == 0 || strcmp(selection,"Q") == 0)
				{
					quit = 1;
				}
						
				else if(strcmp(selection,"o") == 0 || strcmp(selection,"O") == 0)
				{
					BackupFile(outfile);
					file_chk = 1;
				}
			}
		}
	}
	
	return quit;
}

void remove_ext(char *input_file, char *output_file, int backup_file)
{
	/*
	----------------------------------------
	| this function purpose is to remove a |
	| extenision and add the according     |
	| extension  						   |
	----------------------------------------
	*/
	char *out;
	char *temp;
	int length;
	const char ch = '.';
	int ext = 0;
	
	int j;
	
	//printf("tempout = %s\n", output_file);
	if(strcmp(output_file,"") == 0)
	{	
		//printf("tempout = %s\n", output_file);
		strcpy(output_file, input_file);
		//printf("tempout = %s\n", output_file);
		out = strchr(output_file,ch);
		length = strlen(out);  // gets length of file ext.
		for(j = 0; j<length;j++)
		{
			output_file[strlen(output_file)-1] = '\0';
		}
	
		if(backup_file == 1)
		{
			ext = 4;
			ExtensionAppend(output_file,ext);
		}
		if(backup_file == 2)
		{
			ext = 3;
			ExtensionAppend(output_file,ext);
		}
	}
}


//Checks to see if the specified file exists
int FileCheck(char* filename)
{
	struct stat buffer;
	int file_chk;
	file_chk = stat(filename, &buffer);
	return file_chk;
}

//Generates a backup file
void BackupFile(char* outpfile)
{
	char *tempout;
	tempout = strdup("");
	remove_ext(outpfile,tempout,1);
//	printf("tempout = %s\n", tempout);	
	copy_files(outpfile,tempout);	
}

//Generates a listing file
FILE* ListFile(char* outpfile)
{
	FILE* listfile;
	char *listfile_name;
	listfile_name = strdup("");
	
	remove_ext(outpfile,listfile_name,2);

	listfile = fopen(listfile_name,"w+");
	return listfile;
}

//Generates a temp file
FILE* TempFile()
{
	FILE* tempfile;
    char *tempfile_name = "group3andortingleyjunk.bin";
    
    tempfile = fopen(tempfile_name, "w+");
    return tempfile;
    
    //copy_files(outpfile,tempfile);

}

//Copies text from the input file to the output file(s)
void copy_files(char *filein, char *fileout)
{
	// copy text from input file to output file
	char c;
	FILE* incopy;
	FILE* outcopy;
	incopy = fopen(filein,"r");
	outcopy = fopen(fileout,"w");
	c=fgetc(incopy);
//	printf("%c",c);
	while(c != EOF)
	{
		fputc(c, outcopy);
		c=fgetc(incopy);
//		printf("%c",c);
	}
	fclose(incopy);
	fclose(outcopy);
}

FILE* open_file(char* file_name, char* flag)
{
	FILE* file = fopen(file_name,flag);
	return file;
}

void close_files(FILE** infile, FILE** outfile, FILE** listfile, FILE** tempfile)
{
	fclose(*infile);
	fclose(*outfile);
	fclose(*listfile);
	fclose(*tempfile);
 	if (remove("group3andortingleyjunk.bin") != 0)
		printf("Err: Unable to delete temp file");
  
   return 0;
}
