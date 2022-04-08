package day0316;

import java.util.Scanner;

public class Ex10For {
	public static void main(String[] args) {
		/*
		 * (예)
		 * 1. 지수승 구하기
		 * 2. 숫자 N 까지의 합계 구하기
		 * 3. 숫자 N 까지의 팩토리얼 구하기
		 * 4. 종료
		 */
		Scanner sc = new Scanner(System.in);
		int menu;
		while(true) {
			System.out.println("1. 지수승 구하기");
			System.out.println("2. 숫자 N 까지의 합계 구하기");
			System.out.println("3. 숫자 N 까지의 팩토리얼 구하기");
			System.out.println("4. 종료");
			System.out.print("선택> ");
			
			menu = sc.nextInt();
			
			if(menu == 4) {
				System.out.println("프로그램을 종료합니다.");
				break;
			}
			
			switch (menu) {
			case 1:
			{
				int x, y, r = 1;
				System.out.print("지수승을 구할 x, y 두 숫자 입력: ");
				x = sc.nextInt();
				y = sc.nextInt();
				for(int i=0; i<y; i++) {
					r *= x;
				}
				System.out.println(x + "의 " + y + "승은 " + r + "입니다.");
			}
				break;
			case 2:
			{
				int n, sum = 0;
				System.out.print("합계를 구할 n값 입력: ");
				n = sc.nextInt();
				for(int i=0; i<n; i++) {
					sum += i + 1;
				}
				System.out.printf("1부터 %d까지의 합은 %d입니다.\n", n, sum);
			}
				break;
			case 3:
			{
				int n, result = 1;
				System.out.print("숫자 입력:");
				n = sc.nextInt();
				for(int i=0; i<n; i++) { // 5*4*3*2*1 == 1*2*3*4*5
//					result *= n - i;
					result *= i + 1;
				}
				System.out.printf("%d!은 %d입니다.\n", n, result);
			}
				break;
			default:
				System.out.println("*** 메뉴를 다시 선택하세요 ***");
			}
		}
		sc.close();
	}
}
