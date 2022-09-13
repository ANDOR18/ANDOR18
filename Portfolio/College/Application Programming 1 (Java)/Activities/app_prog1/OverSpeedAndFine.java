package app_prog1;
import java.util.Scanner;
public class OverSpeedAndFine {
	static Scanner input = new Scanner(System.in);
	public static void main(String[] args) {
		
		double overSpeed;
		double fine = 0;
		
		System.out.println("Enter the amount over the speed: ");
		overSpeed = input.nextDouble();
		if(0 < overSpeed && overSpeed <= 5) 
		{
			fine = 20;
		}
		
		else if(5 < overSpeed && overSpeed <= 10) 
		{
			fine = 75;
		}
		
		else if(10 < overSpeed && overSpeed <= 15) 
		{
			fine = 150;
		}
		
		else if(overSpeed > 15)
		{
			fine = 170;
		}
		
		System.out.println("fine = "+fine);

		
	}

}
