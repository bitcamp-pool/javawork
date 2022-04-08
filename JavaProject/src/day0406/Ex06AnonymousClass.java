package day0406;

abstract class AbstA {
	abstract public void hello();
}
interface InterAnony {
	public void process();
}
// 익명 클래스


public class Ex06AnonymousClass {
	AbstA aa = new AbstA() { // 추상클래스를 오버라이드 하지 않고 익명 객체로 생성 가능

		@Override
		public void hello() {
			System.out.println("hello : 익명 내부클래스에서 구현함");
		}
	};
	
	InterAnony ia = new InterAnony() {
		
		@Override
		public void process() {
			System.out.println("process : 익명 내부클래스에서 구현함");
		}
	};
	
	public static void main(String[] args) {
		
		Ex06AnonymousClass ex = new Ex06AnonymousClass();
		ex.aa.hello();
		ex.ia.process();
	}
	
	/* AbstA.class
	 * InterAnony.class
	 * Ex06AnonymousClass.class
	 * Ex06AnonymousClass$1.class
	 * Ex06AnonymousClass$2.class
	 */
	
}
