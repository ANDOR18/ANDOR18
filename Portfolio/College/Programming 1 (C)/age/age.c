#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
int age;
printf("Please enter the age "); 
scanf("%d",&age);
if(age>=21)
       printf("You are of legal age\n");
else
    printf("You are underage\n");
return 0;
}