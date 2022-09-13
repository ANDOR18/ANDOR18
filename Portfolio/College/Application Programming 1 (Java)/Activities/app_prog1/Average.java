package app_prog1;
import java.util.*;
public class Average {
	static Scanner input=new Scanner(System.in);
	public static void main(String[] args) {
		/*int[] list;
		int i = 0;
		int MAX_LEN = 5;
		list = new int[MAX_LEN];
		double average = 0;
		for(i=0; i<MAX_LEN; i++)
		{
			System.out.print("Please enter value "+(i+1)+": ");
			list[i] = input.nextInt();
			average += list[i];
		}
		
		average = average/MAX_LEN;
		
		System.out.println("Average: "+average);*/
		other();
		
	}
	public static void other()
	{
		int limit;
		int number;
		int sum;
		int count;
		
		System.out.print("Line 1: Enter the number of integers in the list: ");
		limit = input.nextInt();
		System.out.println();
		
		sum = 0;
		count = 0;
		System.out.println("Line 6: Enter "+limit+" integers.");
		while(count<limit)
		{
			number = input.nextInt();
			sum = sum+number;
			count++;
		}
		System.out.println("The sum of the numbers: "+sum+", The limit: "+limit);
		if(count!=0)
			System.out.println("The average of the numbers is: "+ sum/count);
		else
			System.out.println("No input");
	}
	

}
