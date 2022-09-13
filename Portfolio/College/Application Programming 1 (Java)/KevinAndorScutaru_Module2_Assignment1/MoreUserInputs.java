package KevinAndorScutaru_Module2_Assignment1;
import java.util.Scanner;
public class MoreUserInputs {
	static Scanner input=new Scanner(System.in);
	public static void main(String[] args) 
	{
		String first_name;
		String last_name;
		int grade;
		int student_id;
		String login_name;
		double gpa;
		
		System.out.println("Please enter the following information so I can sell it for a profit!\n");
		
		System.out.print("First name: ");
		first_name = input.next();
		
		System.out.print("Last name: ");
		last_name = input.next();
		
		System.out.print("Grade (9-12): ");
		grade = input.nextInt();
		
		System.out.print("Student ID: ");
		student_id = input.nextInt();
		
		System.out.print("Login: ");
		login_name = input.next();
		
		System.out.print("GPA (0.0-4.0): ");
		gpa = input.nextDouble();
		
		System.out.println("\nYour information:");
		System.out.println("	Login: "+login_name);
		System.out.println("	ID: "+student_id);
		System.out.println("	Name: "+last_name+", "+first_name);
		System.out.println("	GPA: "+gpa);
		System.out.println("	Grade: "+grade);
		

	}

}
