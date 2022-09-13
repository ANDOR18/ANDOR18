package app_prog1;

public class MoreStrings {

	public static void main(String[] args) {
		String s1 = "Susan";
		String s2 = "Susan";
		String s3 = "Robert";
		
		//0 since s1 is identical to s2
		System.out.println(s1.compareTo(s2));
		
		//Returns >0 because S follows R
		System.out.println(s1.compareTo(s3));
		
		//Returns <0 because R precedes S
		System.out.println(s3.compareTo(s1));
		
		String str = "Hello World!";
		str = str.substring(0,7);
		System.out.println(str.equals("Hello"));

	}

}
