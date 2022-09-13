package app_prog1;
import java.util.Scanner;
public class Activity09 {
	static Scanner input=new Scanner(System.in);
	public static void main(String[] args) {
		String name;
		double payRate = 12;
		double hoursWorked;
		double salary;
		
		System.out.print("Enter name: ");
		name = input.next();
		System.out.print("Enter hours worked: ");
		hoursWorked = input.nextDouble();
		salary = payRate * hoursWorked;
		System.out.println("Name: "+name);
		System.out.println("Pay Rate: $"+payRate);
		System.out.println("Hours Worked: "+hoursWorked);
		System.out.println("Salary: $"+salary);
	}

}
