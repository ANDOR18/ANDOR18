package KevinAndorScutaru_Module1_Assignment3;

public class Chicken02 {
	public static void main(String[] args) 
	{
		int monEggs = 100;
		int tuesEggs = 121;
		int wedEggs = 117;
		double dailyAverage = (monEggs+tuesEggs+wedEggs)/3.0;
		double monthlyAverage = dailyAverage * 30;
		double monthlyProfit = monthlyAverage * .18;

		System.out.println("Daily Average: " + dailyAverage);
		System.out.println("Monthly Average: " + monthlyAverage);
		System.out.println("Profit: $" + monthlyProfit);
	}
}
