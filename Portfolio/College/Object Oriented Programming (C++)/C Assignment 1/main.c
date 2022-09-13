#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	int num1, num2, add, multiply;
	
	printf("Enter the number: ");
	scanf("%d", &num1);
	
	printf("Enter the number: ");
	scanf("%d", &num2);
	
	add = num1 + num2;
	multiply = num1*num2;
	
	printf("The numbers added = %d\n", add);
	printf("The numbers multiplied = %d\n", multiply);
	return 0;
}
