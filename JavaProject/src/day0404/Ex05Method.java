package day0404;

class Score {
	private int java;
	private int spring;
	
	// setter method
	public void setJava(int java) {
		this.java = java;
	}
	public void setSpring(int spring) {
		this.spring = spring;
	}
	
	// getter method
	public int getJava() {
		return java;
	}
	public int getSpring() {
		return spring;
	}
}

class Student {
	// 모든 멤버변수는 초기값이 null
	private String name;
	public Score score = new Score();
	
	// setter & getter
	public void setName(String name) {
		this.name = name;
	}
	public String getName() {
		return name;
	}
}

public class Ex05Method {
	public static void main(String[] args) {
		
		Student stu = new Student();
		
		//이름 전달
		stu.setName("송혜교");
		
		// 두 과목의 점수
		stu.score.setJava(90);
		stu.score.setSpring(100);
		
		// 출력(이름, 자바점수, 스프링 점수 출력
		System.out.println("이름 : " + stu.getName());
		System.out.println("자바점수 : " + stu.score.getJava());
		System.out.println("스프링점수 : " + stu.score.getSpring());
	}
}











