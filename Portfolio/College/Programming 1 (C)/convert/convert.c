#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
 {
 	int celsius,fahrenheit;
 	int tempout;
    char letter;
    
	printf("Temperature Conversion\n");
   	printf("F: convert from Fahrenheit to Celsius\n");
   	printf("C: convert from Celsius to Fahrenheit\n");
   	error:
   	letter = "null";
   	printf("Enter the letter: ");
	scanf("%c",&letter); 
    

  	if((letter=='F')||(letter=='f'))
  		{
  		printf("Enter the Fahrenheit temperature ");
  		scanf("%d",&fahrenheit);
		celsius = 5 * (fahrenheit - 32) / 9;
		}
    if((letter=='C')||(letter=='c'))
   		{
		printf("Enter the Celsius temperature ");
    	scanf("%d",&celsius);
  	    fahrenheit = (9 * celsius / 5) + 32;
  		}
  		
  	else
	  	{
  		printf("Please type a valid unit (F\C)\n");
		goto error;
		}
  printf("Temperature Conversion Chart\n");
  printf("Fahrenheit = %d\n",fahrenheit);
  printf("Celsius = %d\n",celsius);
  return 0;
}
