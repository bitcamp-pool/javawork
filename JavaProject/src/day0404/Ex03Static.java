package day0404;

class Bitcamp {
	String name;
	int age;
	static String study;
}

public class Ex03Static {
	
	public static void writeBit(Bitcamp stu) { // Call by ref
		System.out.println("학생명 : " + stu.name);
		System.out.println("학생나이 : " + stu.age);
		System.out.println("학습과목 : " + Bitcamp.study);
		System.out.println("----------------------------");
	}
	
	public static void main(String[] args) {
		
		Bitcamp.study = "java";
		
		Bitcamp younghee = new Bitcamp();
		younghee.name = "이영희";
		younghee.age = 24;
		
		
		Bitcamp chulsoo = new Bitcamp();
		chulsoo.name = "김철수";
		chulsoo.age = 27;
		
		Bitcamp mija = new Bitcamp();
		mija.name = "윤미자";
		mija.age = 30;
		
		// 메서드를 통해서 출력
		writeBit(younghee);
		writeBit(chulsoo);
		writeBit(mija);
	}
}
