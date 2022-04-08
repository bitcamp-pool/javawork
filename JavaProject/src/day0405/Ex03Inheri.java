package day0405;

class Apple {
	private void methodA() {
		System.out.println("super 메서드 A");
	}
	public void methodB() {
		System.out.println("super 메서드 B");
	}
}

class Banana extends Apple {
	public void methodC() {
		System.out.println("sub 메서드 C");
	}
}

public class Ex03Inheri {
	public static void main(String[] args) {
		
		Banana b = new Banana();
		
//		b.methodA(); // 호출불가(private)
		b.methodB(); // 상속된 메서드
		b.methodC();
	}
}
