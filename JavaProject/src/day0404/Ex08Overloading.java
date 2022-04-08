package day0404;

public class Ex08Overloading {
	
	public static void write(String s) {
		System.out.println("문자열 " + s);
	}
	
	public static void write(String s1, String s2) {
		System.out.println("문자열 " + s1 + ", " + s2);
	}
	
	public static void write(int s) {
		System.out.println("정수값 " + s);
	}
	
	public static void write(String[] s) {
		System.out.println("문자열 배열 ");
		for (String a : s)
			System.out.print(a + ", ");
		System.out.println();
	}
	
	// 합계를 구하는 overloading 메서드
	public static int sum(int a, int b) {
		return a+b;
	}
	public static double sum(double a, double b) {
		return a + b;
	}
	
	public static void main(String[] args) {
		write(100);
		write("사과");
		write("red", "pink");
//		write("yello", "orange", "pink") 오류
		
		String[] s = {"red", "orange", "pink", "green"};
		write(s);
		
		System.out.println(sum(2, 3));
		System.out.println(sum(1.2, 6.3));
//		System.out.println(sum("red", 5)); 오류
		
	}
}
