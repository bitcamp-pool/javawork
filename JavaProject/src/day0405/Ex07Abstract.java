package day0405;

// 추상(abstract)메서드를 한개 이상 포함한 경우 반드시 추상클래스로 선언
// abstract 클래스는 일반 메서드와 추상메서드도 모두 구현 가능
abstract class Parent {
//	public void process() {
//		System.out.println("부모가 딱히 하는 일이 없음");
//	}
	// process 가 하는 일은 없지만 오버라이드를 위해서 메서드 존재가 필요
	public abstract void process(); // 미완성의 메서드(abstract:추상화)로 구현한다.
	public void titile() {
		System.out.println("부모만이 하는 일 처리");
	}
}
////////////////////////////////////////
class ChildA extends Parent {
	@Override
	public void process() {
		System.out.println("페이트 칠을 합니다.");
	}
}
///////////////////////////////////////
class ChildB extends Parent {
	@Override
	public void process() {
		System.out.println("집안 청소를 합니다.");
	}
}
///////////////////////////////////////
public class Ex07Abstract {
	
	public static void process(Parent p) {
		p.titile(); // 부모만이 가진 메서드 호출 가능
		// 다형성 처리
		p.process(); // 오버라이드된 메서드만 호출이 가능
	}
	
	public static void main(String[] args) {
		
//		process(new Parent()); // 추상클래스는 자체 인스턴스(객체생성) 불가
		
		process(new ChildA());
		process(new ChildB());
	}
}










