package app_prog1;

public class StringExamples {

	public static void main(String[] args) {
		String sentence="Programming with java";
		String str1;
		String str2;
		
		sentence = "Now is the time for the birthday party.";
		
		
		System.out.println(sentence.substring(7,12));
		System.out.println(sentence.substring(7,22));
		System.out.println(sentence.substring(4,10));
		
		str1 = sentence.substring(0,8);
		str2 = sentence.substring(2,12);
		
		System.out.println(str1);
		System.out.println(str2);

		
		System.out.println("Replace 'm' with 'r': "+sentence.replace('m', 'r'));
		/*System.out.println("String length: "+sentence.length());
		System.out.println("the index of 'a' "+sentence.indexOf('a'));
		System.out.println("the index of 'a' after position 7: "+sentence.indexOf('a',7));
		System.out.println("the character in the index 8: "+sentence.charAt(8));*/
	}

}
