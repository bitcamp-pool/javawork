package day0406;

interface InterA {
	public void draw();
}
// 인터페이스가 인터페이스를 상속 받을 경우 extends
interface InterB extends InterA {
	public void play();
}
// 클래스에서 InterB를 구현할 경우 InterA가 가진것도 오버라이드 해야한다.
class My1 implements InterB {
	// ~~My1 오류 기능 이용하여 오버라이드 함수 자동 검색 및 추가
	
	public void show() {
		System.out.println("My1 이 가진 메서드");
	}
	
	@Override
	public void draw() {
		System.out.println("draw");
	}

	@Override
	public void play() {
		System.out.println("play");
	}
}

public class Ex01Interface {
	public static void main(String[] args) {
		
		My1 a1 = new My1();
		a1.draw();
		a1.play();
		a1.show(); // My1만 가지고 있는 메서드(오버라드 메서드 아님)
		
		InterB a2 = new My1();  // InterB의 오버라이드 된 메서드만 호출가능
		a2.draw();
		a2.play(); 
//		a2.show(); ----->(X)
		
		InterA a3 = new My1();
		a3.draw();
//		a3.play(); ----->(X)
		
		
	}
}
