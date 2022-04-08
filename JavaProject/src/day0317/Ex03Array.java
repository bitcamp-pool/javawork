package day0317;

public class Ex03Array {
	public static void main(String[] args) {
		
		char[] ch;
		ch = new char[4];	// 정수는 초기값 0 으로 셋팅
		System.out.println("len = " + ch.length);
		
		System.out.println("** 초기값 출력 **");
		for (int i=0; i<ch.length; i++) {
			System.out.println((int)ch[i]);
		}
		System.out.println("------------------");
		
		for(int i : ch)
			System.out.println(i);
		
		System.out.println("------------------");
		ch[0] = 'A';
		ch[1] = 67;
		ch[2] = 90;
		ch[3] = '*';
		
		System.out.println("** 배열 출력 방법 1");
		for (int i=0; i<ch.length; i++) { // 요소 읽기, 쓰기
			System.out.printf("%3c", ch[i]);
		}
		System.out.println();
		
		System.out.println("** 배열 출력 방법 2");
		for(char c : ch) 				 // 요소 읽기
			System.out.printf("%3c", c);
		
	}
}
