package app_prog1;
import java.util.Scanner;
public class ScannerMethods {

	static Scanner input=new Scanner(System.in);
	public static void main(String[] args) {
		int age;
		double weight;
		String firstName;
		String fullName;
		char mInitial;
		boolean isTrue;
		
		System.out.print("Enter age: ");
		age = input.nextInt();
		System.out.print("Enter weight: ");
		weight=input.nextDouble();
		System.out.print("Enter first name: ");
		firstName = input.next();
		System.out.print("Enter full name: "+input.nextLine());
		fullName = input.nextLine();
		System.out.print("Enter middle initial: ");
		mInitial = input.next().charAt(0);
		System.out.print("Is your information true? ");
		isTrue = input.nextBoolean();
		System.out.println("Name is: "+firstName+" and your full name: "+fullName+" your middle initial: "+mInitial+"."+
		"Weight: "+weight+ "age: "+age+" My personal information is "+isTrue);
	}

}
