package app_prog1;
/*
 * Kevin Andor Scutaru
 * Exam 2	CIS 120
 * Part 2.1
 */

import java.util.Scanner;
public class PersonalInfo {
	static Scanner input = new Scanner(System.in);
	
	
	public static void main(String[] args) {
		String first_name, last_name, phone_num;
		int age;
		char middle_initial;
		
		System.out.print("Enter your first name: ");
		first_name = input.next();
		System.out.print("Enter your last name: ");
		last_name = input.next();
		System.out.print("Enter your middle initial: ");
		middle_initial = input.next().charAt(0);
		System.out.print("Enter your age: ");
		age = input.nextInt();
		System.out.print("Enter your phone number: ");
		phone_num = input.next();
		
		System.out.println("First name: "+ first_name);
		System.out.println("Last name: "+ last_name);
		System.out.println("Middle initial: "+ middle_initial);
		System.out.println("Age: "+ age);
		System.out.println("Phone number: "+ phone_num);
		
	}

}
