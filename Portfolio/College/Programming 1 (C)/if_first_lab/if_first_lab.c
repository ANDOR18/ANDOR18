#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
	int ID1,ID2,ID3,grade1,grade2,grade3;
	int average,Acount=0,high=0;
	
	printf("Enter ID number 1: ");
	scanf("%d",&ID1);
	printf("Enter the grade: ");
	scanf("%d",&grade1);
	
	printf("Enter ID number 2: ");
	scanf("%d",&ID2);
	printf("Enter the grade: ");
	scanf("%d",&grade2);
	
	printf("Enter ID number 3: ");
	scanf("%d",&ID3);
	printf("Enter the grade: ");
	scanf("%d",&grade3);
	
//find the average
	average=(grade1+grade2+grade3)/3;
//count and print the number of grades >90 (A grade)
	if(grade1>=90)
		Acount=Acount+1;
	if(grade2>=90)
		Acount=Acount+1;
	if(grade3>=90)
		Acount=Acount+1;
//find and print the id of the highest grade	
	if((grade1>grade2)&&(grade1>grade3))
		printf("ID%d got the highest grade\n", ID1);
	if((grade2>grade1)&&(grade2>grade3))
		printf("ID%d got the highest grade\n", ID2);
	if((grade3>grade1)&&(grade3>grade2))
		printf("ID%d got the highest grade\n", ID3);
		
//print the IDs of those who failed the class (grades less than 60)
	printf("The following ID's failed the class:\n");
	if(grade1<60)
		printf("Student ID = %d\n", ID1);
	if(grade2<60)
		printf("Student ID = %d\n", ID2);
	if(grade3<60)
		printf("Student ID = %d\n", ID3);
	else
		printf("None\n");

//print out all data read in
	printf("Number of A grades = %d\n", Acount);
	printf("Average grade = %d",average);
	return 0;
}
