package app_prog1;
import java.util.Scanner;

public class Example02 {
	static Scanner input = new Scanner(System.in); 
	public static void main(String[] args) {
			int num;
			String name;
			System.out.println("Enter number: ");
			num=input.nextInt();
			System.out.println("Enter name: ");
			name=input.next();
			System.out.println("Number : "+num);
			System.out.println("My name is "+name);
	}

}
