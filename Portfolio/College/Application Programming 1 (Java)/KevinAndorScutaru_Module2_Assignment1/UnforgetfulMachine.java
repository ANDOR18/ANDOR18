package KevinAndorScutaru_Module2_Assignment1;
import java.util.Scanner;
public class UnforgetfulMachine {
	static Scanner input=new Scanner(System.in);
	public static void main(String[] args) {
		String name;
		int age;
		double pay;
		
		System.out.println("Hello. What is your name? ");
		name = input.next();
		System.out.println("\nHi, "+name+"! How old are you? ");
		age = input.nextInt();
		System.out.println("\nSo you're "+age+", eh? That's not old at all!");
		System.out.println("How much do you make, "+name+"? ");
		pay = input.nextDouble();
		
		System.out.print("\n$"+pay+"! I hope that's per hour and not per year! LOL!");

	}

}
