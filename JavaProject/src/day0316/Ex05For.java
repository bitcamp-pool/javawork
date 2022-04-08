package day0316;

public class Ex05For {
	public static void main(String[] args) {
		int a;
		for(a=1; a<=5; a++) {
			System.out.printf("%3d", a);
		}
		System.out.println();
		
		for(a=5; a>=1; a--) {
			System.out.printf("%3d", a);
		}
		System.out.println();
		
		for(a=1; a<=20; a+=3); {
			System.out.printf("%3d", a);
		}
		System.out.println();
		
//		1~100 짝수 누적합 구하기
		int sum = 0;
		for(int i=0; i<100; i++) {
			if((i+1) % 2 == 1)
				continue; // for는 증감식(i++)으로 이동, while은 조건식으로 이동
			else
				sum += i + 1;
		}
		System.out.println("sum : " + sum);
	}
}
