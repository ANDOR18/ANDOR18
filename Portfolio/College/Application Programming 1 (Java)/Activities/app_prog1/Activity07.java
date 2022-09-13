package app_prog1;
import java.util.Scanner;
public class Activity07 {

	static Scanner console = new Scanner(System.in);
	
	
	public static void main(String[] args) {
		int num1, num2, num3;
		double average;
		
		System.out.println("Please enter 3 integers:");
		num1=console.nextInt();
		num2=console.nextInt();
		num3=console.nextInt();
		
		average = (num1+num2+num3)/3.0;
		
		System.out.println();
		System.out.println("Num1 = "+num1);
		System.out.println("Num2 = "+num2);
		System.out.println("Num3 = "+num3);
		System.out.println("Average = "+average);

	}

}
