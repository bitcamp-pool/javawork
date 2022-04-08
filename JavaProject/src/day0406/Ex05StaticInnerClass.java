package day0406;

class Orange {
	int a = 10;
	static int b=20;
	
	// 내부에서 반드시 static으로 변수가 필요할 때
	// static 클래스는 외부클래스의 인스턴스 변수 접근 불가
	static class Kiwi {
		int c = 30;
		static int d=30;
		
		public void disp() {
//			System.out.println("a=" + a); // 외부클래스의 인스턴스 변수인 a는 접근불가
			System.out.println("b=" + b);
			System.out.println("c=" + c);
			System.out.println("d=" + d);
		}
	}
	
	// 외부 클래스의 메서드에서 static 내부 클래스 선언시
	public void outerDisp() {
		Kiwi kiwi = new Kiwi();
		kiwi.disp();
	}
}

public class Ex05StaticInnerClass {
	public static void main(String[] args) {
		
		Orange orange = new Orange();
		orange.outerDisp();
		System.out.println();
		
		// 외부클래스의 메서드를 거치치 않고 직접 static내부 클래스 호출시
		Orange.Kiwi kiwi = new Orange.Kiwi();
		kiwi.disp();
		/* 
		 * Orange.class
		 * Orange$Kiwi.class
		 */
	}

}
