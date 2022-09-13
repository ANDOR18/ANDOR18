#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
 int grade1,grade2,grade3,final_grade;
  printf("Enter the three grades :");
  scanf("%d%d%d",&grade1,&grade2,&grade3);
  final_grade=(grade1+grade2+grade3)/3;
  printf("student grades = %d %d %d\n",grade1,grade2,grade3);
  printf("The final grade = %d\n",final_grade);
  if(final_grade>=90)
	printf("The student got an A \n");
  else
	if(final_grade>=80)
		printf("The student got a B\n");
	else
		if(final_grade>=70)
			printf("The student got a C\n");
		else
			if(final_grade>60)
				printf("The student got a D\n");
			else
				printf("The student got an F\n");

	if(final_grade>=90)
		{
		  printf("This is an excellent grade\n");
		  printf("This is an honor student\n");
		}

	return 0;
}