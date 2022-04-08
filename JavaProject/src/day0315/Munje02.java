package day0315;

import java.util.Scanner;

/**
3개의 숫자 a, b, c를 입력받아 
가장 큰 수를 출력하시오(삼항연산자 이용)

(예)
3개의 숫자 입력
3 5 7
가장 큰 숫자는 7입니다.
 */
public class Munje02 {
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		int a, b, c;
		int max;
		
		System.out.print("3개의 숫자 입력: ");
		a = sc.nextInt();
		b = sc.nextInt();
		c = sc.nextInt();
		
//		max = (a>b ? a:b) > c ? (a>b ? a:b) : c;
		max = (a>b && a>c) ? a : (b>a && b>c) ? b:c;
		System.out.printf("가장 큰 숫자는 %d입니다.", max);
		
		sc.close();
	}
}
