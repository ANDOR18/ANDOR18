package app_prog1;
import java.util.Scanner;
public class YCounter {
	static Scanner input = new Scanner(System.in);
	public static void main(String[] args) {
		/*int count = 0;
		int max = 8;
		float average = 0;
		int value;
		while (count<max)
		{
			System.out.println("Enter value "+(count+1)+":");
			value = input.nextInt();
			average = average + value;
			count++;
		}
		
		average = average/max;
		System.out.println("Average = "+ average);*/
		checking();

	}
	public static void checking()
	{
		int num;
		int sum=0;
		int count = 0;
		int sentinal = -999;
		System.out.println("Enter positive integers, "+"ending with"+sentinal);
		num=input.nextInt();
		while(num!=sentinal)
		{
			sum=sum+num;
			count++;
			num=input.nextInt();
		}
		if (count!=0)
			System.out.println("The average is "+(sum/count));
		else
			System.out.println("No input");
	}

}
