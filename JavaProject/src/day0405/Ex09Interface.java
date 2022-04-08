package day0405;

// 상수와 추상메서드만 구현 가능
interface InterA {
	int SPEED = 100; // final 상수
	public void speedWrite(); // abstract 메서드
}

// 인터페이스를 구현하는 클래스
class My implements InterA {
	@Override
	public void speedWrite() {
//		SPEED = 120; 상수이므로 값 변경 불가
		System.out.println("나의 스피드는 " + SPEED + "입니다.");
	}
}

public class Ex09Interface {
	public static void main(String[] args) {
		InterA a = new My();
		a.speedWrite();
	}
}
