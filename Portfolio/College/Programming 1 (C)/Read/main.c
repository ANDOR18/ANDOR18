#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	int count;
	double  num, sum, avg;
	char name[10];
	
	printf("Enter your name: ");
	scanf("%s", name);
	
	printf("%s, Enter values for an average, 0 to end: \n", name);
	scanf("%lf",&num);
	while(num != 0)
	{	
	sum = sum + num;
	count = count+1;
	scanf("%lf",&num);	
	}
	
	printf("=======================\n");
	avg = sum/count;
	printf("%s, The average is %lf",name, avg);
	
	return 0;
}
