package KevinAndorScutaru_Module2_Assignment1;
import java.util.Scanner;
public class AgeInFiveYears {
	static Scanner input=new Scanner(System.in);
	public static void main(String[] args) {
		String name;
		int age;
		
		System.out.print("Hello. What is your name? ");
		name = input.next();
		
		System.out.print("\nHi, "+name+"! How old are you? ");
		age = input.nextInt();
		
		System.out.println("\nDid you know that in five years you will be "+(age+5)+" years old?");
		System.out.println("And five years ago you were "+(age-5)+"! Imagine that!");
	}

}
