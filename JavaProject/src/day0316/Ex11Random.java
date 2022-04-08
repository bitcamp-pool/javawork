package day0316;

public class Ex11Random {
	public static void main(String[] args) {
		/*
		 * 임의의(랜덤) 수를 구하는 방법
		 * 1. Math.random
		 * 2. Random 클래스		 
		 */
		for(int i=0; i<5; i++) {
			double a = Math.random();
			System.out.printf("%.2f, ", a);
		}
		System.out.println("\n1)---------------------------------------------------");
		
		System.out.println("0~99 사이의 난수 구하기");
		for(int i=0; i<5; i++) {
			int a = (int) (Math.random() * 100);
			System.out.printf("%d, ", a);
		}
		System.out.println("\n2)---------------------------------------------------");
		
		System.out.println("1~100 사이의 난수 구하기");
		for(int i=0; i<5; i++) {
			int a = (int) (Math.random() * 100) + 1;
			System.out.printf("%d, ", a);
		}
		System.out.println("\n3)---------------------------------------------------");
		
		System.out.println("임의의 알파벳 A~Z(65~90) 구하기");
		for(int i=0; i<5; i++) {
			int a = 65 + (int) (Math.random() * 26);
			char ch = (char)a;
			System.out.printf("%c, ", ch);
		}
		System.out.println("\n4)---------------------------------------------------");
		
	}
}
