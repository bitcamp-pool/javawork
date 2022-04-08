package day0405;

class SuperObj {
	public void process() {
		System.out.println("super 부모가 공통적인 일을 처리합니다");
	}
}
////////////////////////////////////////////////////
class Draw extends SuperObj {
	@Override
	public void process() {
		super.process();
		System.out.println("나는 그림을 그려요!!!");
	}
}
////////////////////////////////////////////////////
class Game extends SuperObj {
	@Override
	public void process() {
		super.process();
		System.out.println("나는 게임을 해요!!!");
	}
}

public class Ex06Inheri {
	
	public static void process(SuperObj obj) {
		obj.process();
	}
	
	public static void main(String[] args) {
		
//		SuperObj obj = null;
//		
//		obj = new Draw();
//		obj.process(); // Draw가 가진 process가 호출
//		
//		obj = new Game();
//		obj.process(); // Game이 가진 process가 호출
		
		// 다형성 처리
		process(new Draw()); // 그림 그리는 일을 처리
		process(new Game()); // 게임에 관한 일을 처리
	}
}








