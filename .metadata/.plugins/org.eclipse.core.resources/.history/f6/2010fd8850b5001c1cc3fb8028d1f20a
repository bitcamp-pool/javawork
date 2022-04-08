package day0406;

// Member 내부 클래스 : 다중상속이 안되므로 ...
class Outer {
	int a = 10;
	static int b=20;
	
	// 내부 클래스
	class Inner {
		int c=30;
//		static int d=40; //member 내부 클래스에서 static변수 선언 불가
		public void disp() {
			System.out.println("a=" + a);
			System.out.println("b=" + b);
			System.out.println("c=" + c);
		}
	}
	
	public void outerDisp() {
		// 내부 클래스 선언
		Inner in = new Inner();
		in.disp();
	}
}
public class Ex04InnerClass {
	public static void main(String[] args) {
		
		// 외부 클래스가 가진 메서드 호출(메서드에서 내부클래스 선언 시)
		Outer out = new Outer();
		out.outerDisp();
		System.out.println();
		
		// 외부클래스의 메서드를 거치지 않고 바로 내부 메서드를 호출하고자 할 경우
		//                 외부객체생성.내부객체생성
		Outer.Inner inner = new Outer().new Inner();
		inner.disp();
		/* Outer.class 			외부클래스
		 * Outer$Inner.class    외부클래스$내부클래스
		 */
	}
}
