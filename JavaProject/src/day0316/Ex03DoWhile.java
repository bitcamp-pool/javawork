package day0316;

public class Ex03DoWhile {
	public static void main(String[] args) {
		int a = 10;
		System.out.println("***while***");
		while(a < 10) {
			System.out.println(a++);
		}
		
		System.out.println("***do~while***");
		do {
			System.out.println(a++);
		} while(a < 10);
		
		System.out.println("--------------------------");
//		1~100까지의 누적합 구하기(1+2+3+.....+100)
		a = 0;
		int sum = 0;
		while(++a <= 100) {
			sum += a;
		}
		System.out.println("총합: " + sum);
		
//	    1~100까지 짝수합, 홀수합
		a = 0;
		int esum = 0, osum = 0;
		while(++a <= 100) {
			if (a % 2 == 0)
				esum += a;
			else
				osum += a;
		}
		System.out.println("짝수합계: " + esum);
		System.out.println("홀수합계: " + osum);
	}
}
