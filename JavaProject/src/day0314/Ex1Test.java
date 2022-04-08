package day0314;

public class Ex1Test {

	public static void main(String[] args) {
		
		System.out.println("0번인자 args[0]: " + args[0]);
		System.out.println("1번인자 args[1]: " + args[1]);

		if(args[0].equals("kor"))
			System.out.print("안녕 자바! ");
		if(args[0].equals("eng"))
			System.out.print("Hello Java! ");
		
		System.out.println();

		System.out.println("ver: " + args[1]);
	}
}
