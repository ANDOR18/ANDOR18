#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	double balance, deposit1, deposit2, check1, check2, check3, final_balance, check_sum;

	printf("Enter your beginning balance: $");
	scanf("%lf", &balance);
	
	printf("Enter the first deposit: $");
	scanf("%lf", &deposit1);
	
	printf("Enter the second deposit: $");
	scanf("%lf", &deposit2);
	
	printf("Enter the first check: $");
	scanf("%lf", &check1);
	
	printf("Enter the second check: $");
	scanf("%lf", &check2);
	
	printf("Enter the third check: $");
	scanf("%lf", &check3);
	
	check_sum = check1 + check2 + check3;
	
	final_balance = balance + (deposit1*1.05 + deposit2*1.05) - check_sum;
	
	printf("Balance: $%lf\nFirst Deposit: $%lf\nSecond Deposit: $%lf\nFirst Check: $%lf\nSecond Check: $%lf\nThird Check: $%lf\nFinal Balance: $%lf", balance, deposit1, deposit2, check1, check2, check3, final_balance);
	
	
	
	
	return 0;
}
