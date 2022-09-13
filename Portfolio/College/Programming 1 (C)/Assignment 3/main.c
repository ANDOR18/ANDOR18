#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	//Sets up the variables
	char firm[30] = "Handyfirm Construction";
	char customer[20] = "Ima Customer";
	
	float labor_hours, material_cost;
	
	float labor_cost, job_fee, discount, final_amount;
	
	
	//prompts user for hours and material cost
	printf("Enter the amount of labor hours: ");
	scanf("%lf",&labor_hours);
	
	printf("Enter the cost of materials: $");
	scanf("%lf", &material_cost);
	
	
	//calculate labor hours and material amount
	labor_cost = labor_hours * 50;
	job_fee = labor_cost + material_cost;
	
	

	//determines percentage discounted
	if (job_fee < 5000)
	{
		discount = 0;
	}
	
	else
	{	
		if (job_fee >= 5000 && job_fee < 10000)
		{
			discount = 0.05;	
		}
		
		else
		{
			
			if (job_fee >= 10000 && job_fee < 20000)
			{
				discount = .10;				
			}
			
			else
			{
				
				if (job_fee >= 20000)
				{
					discount = .20;
				}
				
			}
			
		}	
	}
	
	//calculates total discount
	discount = job_fee * discount;
	
	//calculates final amount
	final_amount = job_fee - discount;
	
	//prints the results
	printf("\n%s\nCustomer: %s\nNumber of Hours = %lf\nLabor Cost = $%lf\nMaterials = $%lf\nJob Fee = $%lf\nDiscount = $%lf\n\n\nFinal Amount Due = $%lf",
	 firm, customer, labor_hours, labor_cost, material_cost, job_fee, discount, final_amount);
	
	

	
	
	
	return 0;
}
