package day0318;

public class Ex02StringCompare {
	public static void main(String[] args) {
		
		System.out.println("Apple".compareTo("Apple"));		// 같을 경우  0
		System.out.println("Apple".compareTo("Banana")); 	// 같을 경우 -1
		System.out.println("Hello".compareTo("Hi"));	    // -4
		System.out.println("Hello".compareTo("Apple"));	    //  7
		
	}
}
