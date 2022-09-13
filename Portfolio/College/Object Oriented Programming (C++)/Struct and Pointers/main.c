#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	struct list 
	{
	int num;
	char let;	
	};

	struct list pair;
	printf("Input the number: ");
	scanf("%d", &pair.num);
	fflush(stdin);
	printf("Input the letter: ");
	scanf("%c", &pair.let);
	fflush(stdin);
	printf("The combination is %c%d", pair.let, pair.num);
	

	pointer_func();
	
	return 0;
}


int pointer_func()
{
	char *ptr, s;
	s = "K";
	ptr = &s;
	printf("%c", *ptr);
} 
