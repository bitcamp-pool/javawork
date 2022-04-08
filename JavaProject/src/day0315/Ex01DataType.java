package day0315;

public class Ex01DataType {

	public static void main(String[] args) {
		// 기본형 연습
		char ch  = 'A';
		char ch2 = '가';
		char ch3 =  67;
		char ch4 =  (char) (ch3 + 2); // 강제형변한
		
		System.out.println(ch);
		System.out.println(ch2);
		System.out.println(ch3);
		System.out.println(ch4);
		System.out.println(ch3 + 2);
		System.out.println((char) (ch3 + 2));
		
		int a = 7;
		int b = 4;
		System.out.println(a / b);
		System.out.println(a /(double)b);
		System.out.println((double) (a / b));
	}

}
