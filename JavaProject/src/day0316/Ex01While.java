package day0316;

public class Ex01While {
	public static void main(String[] args) {
		int a = 0;
		while(++a <= 5) { // 증가 후 비교
			System.out.println(a);
		}
		System.out.println("빠져나온 후의 a값: " + a);
		
		a = 0;
		while(a++ <= 5) { // 비교 후 증가
//	    while(a++ <  5)
			System.out.println(a);
		}
		System.out.println("빠져나온 후의 a값: " + a);
		
//		1~5 까지 출력
		a = 0;
		while(true) {
			System.out.println(++a);
//			if(a == 5)
//				break;
		}
//		System.out.println("빠져나온 후의 a값: " + a);
	}
}
