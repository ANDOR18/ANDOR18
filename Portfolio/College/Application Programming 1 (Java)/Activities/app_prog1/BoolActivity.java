package app_prog1;
import java.util.Scanner;

public class BoolActivity {
	
	static Scanner input=new Scanner(System.in);
	public static void main(String[] args) {
		boolean drivingUnderAge = false;
		int age;
		
		System.out.print("Enter an age: ");
		age = input.nextInt();
		
		if (age <= 18)
		{
			drivingUnderAge = true;
		}
		
		System.out.print(drivingUnderAge);

	}

}
