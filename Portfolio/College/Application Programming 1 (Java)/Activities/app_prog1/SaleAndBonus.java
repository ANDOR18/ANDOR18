/*
 * Kevin Andor Scutaru
 * Exam 2	CIS 120
 * Part 2.2
 */

package app_prog1;
import java.util.Scanner;
public class SaleAndBonus {
	static Scanner input = new Scanner(System.in);
	public static void main(String[] args) {
		double sale, bonus;
		
		
		System.out.print("Enter the sale: ");
		sale = input.nextDouble();
		
		if(sale >= 30000) 
			bonus = .15;
		else if((sale > 15000) && (sale < 30000)) 
			bonus = .10;
		else
			bonus = .05;
		
		System.out.println("Sale: $" + sale);
		System.out.println("Bonus: " + bonus);
	}

}
