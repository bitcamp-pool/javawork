package day0404;

class Hello {
	int year, month, day;
	
	Hello(int year, int month, int day){
		this.year = year;
		this.month = month;
		this.day = day;
	}
	
	public void write() {
		System.out.println(year + "년" + month + "월" + day + "일생입니다.");
	}
}

class Hello2 {
	int year, month, day;
	
	private Hello2(int year, int month, int day){
		this.year = year;
		this.month = month;
		this.day = day;
	}
	
	public static Hello2 getInstance() {
		return new Hello2(2010, 12, 25);
	}
	
	public void write() {
		System.out.println(year + "년" + month + "월" + day + "일생입니다.");
	}
}

public class Ex11Singleton {
	public static void main(String[] args) {
		
//		Hello h1 = new Hello(); // 1개라도 정의되어 있다면 기본 생성자는 자동으로 호출되지 않는다. 
		
		Hello h1 = new Hello(1970, 10, 21);
		h1.write();
		
//		Hello2 h2 = new Hello2(2005, 11 25);
		/*
		 * 어떤 클래스가 최초 한번만 메모리를 할당하고(Static) 그 메모리에 
		 * 객체를 만들어 사용하는 디자인 패턴= 을 의미한다.
		 * 즉 생성자의 호출이 반복적으로 이뤄져도 실제로 생성되는 
		 * 객체는 최초 생성된 객체를 반환 해주는 것이다.
		 */
		Hello2 h2 = Hello2.getInstance(); // 싱글톤
		h2.write();
	}
}
