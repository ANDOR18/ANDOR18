package app_prog1;
import java.util.Scanner;
public class SumAndAverage1 {
	static Scanner input = new Scanner(System.in);
	public static void main(String[] args) {
		int num;
		int sum = 0;
		int counter = 1;
		double average;
		
		while(counter <= 5)
		{
			System.out.print("Enter int #"+counter+": ");
			num = input.nextInt();
			sum = sum + num;
			counter++;
		}
		average = sum/(double)(counter-1);
		System.out.println("Sum = " + sum);
		System.out.println("Average = " + average);
		

	}

}
