#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
int age;
char gender;
printf("Please enter the gender "); 
scanf("%c",&gender);
printf("Please enter the age "); 
scanf("%d",&age);
if((age>=18)&&(gender=='M'))
       printf("You must regeister for the draft\n");
printf("Gender = %c Age = %d",gender,age);
return 0;
}