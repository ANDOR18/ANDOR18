package app_prog1;
import java.util.Scanner;
public class SumAndAverage2 {
	static Scanner input = new Scanner(System.in);
	public static void main(String[] args) {
		int num;
		int sum = 0;
		double average;
		int counter;
		for(counter = 1; counter <=5; counter++)
		{
			System.out.print("Enter int #"+counter+": ");
			num = input.nextInt();
			sum = sum + num;
		}
		average = sum/(double)(counter-1);
		System.out.println("Sum = " + sum);
		System.out.println("Average = " + average);
		

	}

}