package app_prog1;
import java.util.Scanner;
public class IfElse {
	static Scanner input = new Scanner (System.in);
	public static void main(String[] args) {
		//double hours, rate, wages;
		
		/*System.out.print("Enter hours worked: ");
		hours = input.nextDouble();
		System.out.print("Enter pay rate: ");
		rate = input.nextDouble();
		if (hours>40.0) 
		{
			wages = 40*rate+1.5*rate*(hours-40);
		}
		else
			wages = rate*hours;
		System.out.print("The salary of an employee's weekly is: "+wages);*/
		//vote();
		bonus();

	}
	
	static void vote() 
	{
		int age;
		
		System.out.print("Enter your age: ");
		age = input.nextInt();
		
		if (age >= 18)
		{
			System.out.println("You are eligible to vote.");
			System.out.print("You are not a minor.");
		}
		
		else 
		{
			System.out.println("You are not eligible to vote.");
			System.out.print("You are a minor.");
		}
	}
	
	static void bonus()
	{
		double sale, bonus;
		System.out.print("Enter the sale: ");
		sale = input.nextDouble();
		if (sale > 20000) 
		{
			bonus = .1;
		}
		else if ((sale > 10000) && (sale <= 20000)) 
		{
			bonus = .05;
		}
		else 
		{
			bonus = 0;
		}
		System.out.print("bonus = " + bonus);

	}
}
