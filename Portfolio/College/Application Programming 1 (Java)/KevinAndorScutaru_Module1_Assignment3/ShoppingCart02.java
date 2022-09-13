package KevinAndorScutaru_Module1_Assignment3;

public class ShoppingCart02 {

	public static void main(String[] args) {
		String customerName = "Alex";
		String item = "shirt";
		String message = customerName + " wants to purchase a " + item;
		
		//Declare and initialize numeric fields: price, tax, quantity
		double price = 10.0;
		double tax = .06;
		int quantity = 2;
		
		//Declare and assign a calculated totalPrice
		double totalPrice = (price*quantity)*tax + (price*quantity);
		
		//Modify message to include quantity
		message = customerName + " wants to purchase "+ quantity + " " + item + "(s)";
		
		System.out.println(message);
		
		//Print another message with the total cost
		System.out.println("Total cost with tax is: $" + totalPrice);
	}

}
