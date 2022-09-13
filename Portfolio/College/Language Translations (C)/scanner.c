#include "scanner.h"
#include "file_util.h"

token scanner(int destructive, char** buffer, FILE*** infile, FILE*** listfile)
{
	/* Scan for tokens, and print evetything in the input file to the listing file with
	 line numbers and errors found (maintain file position and keep line count)*/
	char character;
	char* line_buffer;
	int position_val;
	fpos_t position;
	fpos_t start_position;
	token tok;
	int flag = 0;
	int token_number;
    char acctual_token[15];
    char token_string[15];
	//Upon entry, clear the token buffer
	*buffer = strdup("");
	
	//If the destructive flag isnt ticked, save the position
	if(destructive != 1)
	{
		fgetpos(**infile, &start_position);
	}
	
//Take in characters
	character = fgetc(**infile);

//If end of file, return token
	if(feof(**infile))
	{
		tok = SCANEOF;
	} 

	else{
		
//If end of line, skip white space to new line
	if(character == '\n')
	{	
		while(isspace(character)==0)
		{
			character = fgetc(**infile);
			fgetpos(**infile, &position);
		}
		
		flag = 1;
	}
	
//Else continue down list of possible symbols
		else if(isspace(character)!=0)
		{
			flag = 1;
		}
		else if (isalnum(character)!=0)
		{
			while(isalnum(character)!=0)
			{
				fgetpos(**infile, &position);
				//printf("%c" ,character);
				if (isalnum(character)!=0)
				{
					add_char(buffer, character);
					character = fgetc(**infile);
					if (ispunct(character)!=0)
					{
						fsetpos(**infile, &position);
					}
				}
			}
		}
			
		else if(ispunct(character)!=0)
		{
			if(character == '-')
			{
				add_char(buffer, character);
				fgetpos(**infile, &position); 
				character = fgetc(**infile);
				if(character == '-')
				{
					flag = 1;
					while(ispunct(character)!=0 || isalnum(character)!=0 ||isdigit(character)!=0 || character != '\n')
					{
						character = fgetc(**infile);
						fgetpos(**infile, &position);
						fsetpos(**infile, &position);
						add_char(buffer, character);	
					}
				//	*buffer = strdup("");
					fgetpos(**infile, &position);
					fsetpos(**infile, &position);
				}
				
				else if (isdigit(character)!=0)
				{
					while(isdigit(character)!=0)
					{
						fgetpos(**infile, &position);
						//printf("%c" ,character);
						if (isdigit(character)!=0)
						{
							add_char(buffer, character);
							character = fgetc(**infile);
							if (ispunct(character)!=0)
							{
								fsetpos(**infile, &position);
							}
						}
					}
				}
			
				else
				{
					fgetpos(**infile, &position);
					fsetpos(**infile, &position);
				}
			}
			
			else if(character == '<')
			{
				add_char(buffer, character);
				fgetpos(**infile, &position); 
				character = fgetc(**infile);
				if((character == '='||character == '>'))
				{
					//add_char(line_buffer, character);
					add_char(buffer, character);
				}
				else
					fsetpos(**infile, &position);
				}
			
			else if(character == '>')
			{
				add_char(buffer, character);
				fgetpos(**infile, &position); 
				character = fgetc(**infile);
				if(character == '=')
				{
					//add_char(line_buffer, character);
					add_char(buffer, character);
				}
				else
				{
					fsetpos(**infile, &position);
				}
			}
			
			else if(character == ':')
			{
			//	printf("hit");
				add_char(buffer, character);
				fgetpos(**infile, &position); 
				character = fgetc(**infile);
				if(character == '=')
				{
					//add_char(line_buffer, character);
					add_char(buffer, character);
				}
				else
				{
					fsetpos(**infile, &position);
				}
			}
				
			else{
				add_char(buffer, character);
				//add_char(line_buffer, character);
			}	
		}
	}
	
//If EOF
	if(tok == SCANEOF)
	{
    	if(destructive != 1)
		{
			fsetpos(**infile, &start_position);
		}
		
		return tok;
	}

//If new line or space
	else if(flag == 1)
	{
		*buffer = strdup("");
		return -1;
	}
	
//If other symbol
	else
	{
		tok = check_reserved(buffer);
		if(destructive != 1)
		{
			fsetpos(**infile, &start_position);
		}
		return tok;
	}
	
}


token check_reserved(char** buffer) //Returns the token of the string
{
        token tok;
        char convert[100];
        int i;
        strcpy(convert, *buffer);
 //       printf("hit");
        for(i = 0; i < strlen(convert); ++i)
		{
        	convert[i] = tolower((unsigned char)convert[i]);
    	}
    //    printf("Token entered: %s\n", buffer);
        if (strcmp(convert,"begin") == 0){
            tok = BEGIN;
        }

        else if(strcmp(convert,"end") == 0){
            tok = END;
        }

        else if(strcmp(convert,"read") == 0){
            tok = READ;
        }

        else if(strcmp(convert,"write") == 0){
            tok = WRITE;
        }

        else if(strcmp(convert,"if") == 0){
            tok = IF;
        }

        else if(strcmp(convert,"then") == 0){
            tok = THEN;
        }

        else if(strcmp(convert,"else") == 0){
            tok = ELSE;
        }

        else if(strcmp(convert,"endif") == 0){
            tok = ENDIF;
        }

        else if(strcmp(convert,"while") == 0){
            tok = WHILE;
        }

        else if(strcmp(convert,"endwhile") == 0){
            tok = ENDWHILE;
        }

        else if(strcmp(convert,"false") == 0){
            tok = FALSEOP;
        }

        else if(strcmp(convert,"true") == 0){
            tok = TRUEOP;
        }

        else if(strcmp(convert,"null") == 0){
            tok = NULLOP;
        }

        else if(strcmp(convert,"(") == 0){
            tok = LPAREN;
        }

        else if(strcmp(convert,")") == 0){
            tok = RPAREN;
        }

        else if(strcmp(convert,";") == 0){
            tok = SEMICOLON;
        }

        else if(strcmp(convert,",") == 0){
            tok = COMMA;
        }

        else if(strcmp(convert,":=") == 0){
            tok = ASSIGNOP;
        }

        else if(strcmp(convert,"+") == 0){
            tok = PLUSOP;
        }

        else if(strcmp(convert,"-") == 0){
            tok = MINUSOP;
        }

        else if(strcmp(convert,"*") == 0){
            tok = MULTOP;
        }

        else if(strcmp(convert,"/") == 0){
            tok = DIVOP;
        }

        else if(strcmp(convert,"!") == 0){
            tok = NOTOP;
        }

        else if(strcmp(convert,"<") == 0){
            tok = LESSOP;
        }

        else if(strcmp(convert,"<=") == 0){
            tok = LESSEQUALOP;
        }

        else if(strcmp(convert,">") == 0){
            tok = GREATEROP;
        }

        else if(strcmp(convert,">=") == 0){
            tok = GREATEREQUALOP;
        }

        else if(strcmp(convert,"=") == 0){
            tok = EQUALOP;
        }

        else if(strcmp(convert,"<>") == 0){
            tok = NOTEQUALOP;
        }
		
         else {
  			//Checks to see if alphanum string is ID, INTLITERAL, or ERROR
            int letter = 0, num = 0;
            int id_flag = 0;
            for (i = 0; convert[i] != '\0'; i++)
            {
///                printf("scanner buff: %c", convert[i]);
                if(i == 0)
                {
                    if(convert[i] == '-')
                    {
                        num++;
                    }
                }
                
                if(isalpha(convert[i]) != 0)
                {
                    letter++;
                    if(i == 0)
                    {
                        id_flag = 1;
                    }
                }
                
                
                else if(isdigit(convert[i]) != 0)
                {
                    if(id_flag == 1)
                    {
                        letter++;
                    }
                    else
                    {
                        num++;
                    }
                }
            }
			
			if(letter == strlen(convert))
			{
				tok = ID;
			}
			else if(num  == strlen(convert))
			{
				tok = INTLITERAL;
			}
			else
			{
				tok = ERROR;
			}
        }


    return tok;
}


char* token_identify(char* buffer,token tok){ //Identifies the string for the token

        char token_string[15];
//        printf("Token entered in identity: %s\n", buffer);

        if(tok == BEGIN ){
            strcpy(token_string,"BEGIN");
        }

        else if(tok == END ){
            strcpy(token_string,"END");
        }

        else if(tok == READ ){
            strcpy(token_string,"READ");
        }

        else if(tok == WRITE){
            strcpy(token_string,"WRITE");
        }

        else if(tok ==IF){
            strcpy(token_string,"IF");
        }

        else if(tok == THEN){
            strcpy(token_string,"THEN");
        }

        else if(tok ==  ELSE){
            strcpy(token_string,"ELSE");
        }

        else if(tok ==  ENDIF){
            strcpy(token_string,"ENDIF");
        }

        else if(tok ==  WHILE){
            strcpy(token_string,"WHILE");
        }

        else if(tok ==  ENDWHILE){
            strcpy(token_string,"ENDWHILE");
        }
		
        else if(tok == ID){
            strcpy(token_string,"ID");
        }

        else if(tok == INTLITERAL){
            strcpy(token_string,"INTLITERAL");
        }

        else if(tok == FALSEOP){
            strcpy(token_string,"FALSEOP");
        }

        else if(tok == TRUEOP){
            strcpy(token_string,"TRUEOP");
        }

        else if(tok == NULLOP){
            strcpy(token_string,"NULLOP");
        }

        else if(tok == LPAREN ){
            strcpy(token_string,"LPAREN");
        }

        else if(tok == RPAREN ){
            strcpy(token_string,"RPAREN");
        }

        else if(tok == SEMICOLON){
            strcpy(token_string,"SEMICOLON");
        }
        
        else if(tok == COMMA){
            strcpy(token_string,"COMMA");
        }
        
        else if(tok == ASSIGNOP){
            strcpy(token_string,"ASSIGNOP");
        }
        
        else if(tok == PLUSOP){
            strcpy(token_string,"PLUSOP");
        }
        
        else if(tok == MINUSOP){
 			strcpy(token_string,"MINUSOP");
        }

        else if(tok == MULTOP){
            strcpy(token_string,"MULTOP");
        }

        else if(tok == DIVOP){
            strcpy(token_string,"DIVOP");
        }

        else if(tok == NOTOP){
            strcpy(token_string,"NOTOP");
        }

        else if(tok == LESSOP){
            strcpy(token_string,"LESSOP");
        }

        else if(tok == LESSEQUALOP){
            strcpy(token_string,"LESSEQUALOP");
        }

        else if(tok == GREATEROP){
            strcpy(token_string,"GREATER");
        }

        else if(tok == GREATEREQUALOP){
            strcpy(token_string,"GREATEREQUALOP");
        }

        else if(tok == EQUALOP){
            strcpy(token_string,"EQUALOP");
        }

        else if(tok == NOTEQUALOP){
            strcpy(token_string,"NOTEQUALOP");
        }
        else if(tok == SCANEOF){
        	strcpy(token_string,"EOF");
		}
        
       else{
    		strcpy(token_string,"ERROR");
        }

    return token_string;
}

void add_char(char** buffer, char character) //Adds a character to the buffer
{
	strncat(*buffer, &character, 1);//check here
}



