package app_prog1;

import java.util.Scanner;
public class ex514 {
	static Scanner input = new Scanner(System.in);
	public static void main(String[] args) {
		/*int sum = 0;
		double average = 0;
		int newNum;
		for (int i = 0; i < 5; i++)
		{
			newNum= input.nextInt();
			sum = sum + newNum;
		}
		average = sum/5;
		System.out.println("The sum is "+sum);
		System.out.println("The average is "+average);*/
		activity();
	}
	public static void activity()
	{
		int sum = input.nextInt();
		int num = input.nextInt();
		for (int i = 1; i <= 3; i++)
		{
			num = input.nextInt();
			sum = sum + num;
		}
		
		System.out.println("Sum = "+sum);
		
	}

}

//nothing
//counts down forever
//10
//nothing
//error
