package day0315;

public class Ex02DataType {
	public static void main(String[] args) {
		byte b1 = 127;
		byte b2 = (byte)3963;
		System.out.println(b1);
		System.out.println(b2);
		
		float  f1 = 123.456789123f;
		double d1 = 123.456789123;
		System.out.println(f1);
		System.out.println(d1);
		
		boolean b = true;
		System.out.println(b);
		System.out.println(!b);
		
		// printf(jdk5이상): 정수%d, 실수%f, 문자%c, 문자열%s
		System.out.printf("f1=%07.1f, d1=%07.2f\n", f1, d1);
		System.out.printf("f1=%7.1f, d1=%7.2f\n", f1, d1);
		char ch = 'A';
		System.out.printf("ch=%c\n", ch);
		
		// "Red", "Blue"
		System.out.println("\"Red\", \"Blue\"");
		// 파일의 경로: '/', '\'
		System.out.println("c:/image/sun.jpg");
		System.out.println("c:\\image\\sun.jpg");
		System.out.println("D:\\bitjava0314\\reference\\img\\popup");
	}
}
