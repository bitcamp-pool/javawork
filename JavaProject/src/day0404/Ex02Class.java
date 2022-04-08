package day0404;

// 파일명과 같아야 public
//public class Apple {	
//}
class Apple {
	// 접근 지정자 연습(같은 패키지내에서는 private을 제외하고 모두 접근 가능)
	int a = 10;
	protected int b = 20;
	@SuppressWarnings("unused")
	private int c = 30;
	public int d = 40;
	
	public final static String MESSAGE = "Hello";
}


public class Ex02Class {
	public static void main(String[] args) {
		
		Apple a1 = new Apple();
		System.out.println(a1.a);
		System.out.println(a1.b);
//		System.out.println(a1.c); // error : private은 같은 클래스 내에서만 접근 가능
		System.out.println(a1.d);
		
		System.out.println(Apple.MESSAGE); // static변수는 클래스명으로 호출
	}
}
