package day0316;

public class Ex02While {
	public static void main(String[] args) {
//		ABCDEFGHIJKLMNOPQRSTUVWXYZ 출력하기
		int a = 65;
		while(true) {
			System.out.print((char)a);
			a++;
			if(a > 90)
				break;
		}
		System.out.println();
		
		char ch = 'A';
		while(true) {
			System.out.print(ch++);
			if(ch > 'Z')
				break;
		}
		System.out.println();
	}
}
