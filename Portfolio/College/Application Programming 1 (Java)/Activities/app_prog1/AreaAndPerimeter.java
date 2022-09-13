package app_prog1;
import java.util.Scanner;
public class AreaAndPerimeter {
	static Scanner console = new Scanner(System.in);
	public static void main(String[] args) {
		double length;
		double width;
		
		System.out.print("Enter the length of the rectangle: ");
		length = console.nextDouble();
		System.out.print("Enter the width of the rectangle: ");
		width = console.nextDouble();
		
		
		System.out.println("The area of the rectangle is: "+(length*width));
		System.out.println("The perimeter of the rectangle is: "+((length+width)*2));
	}

}
