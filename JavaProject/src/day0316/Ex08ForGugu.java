package day0316;

import java.util.Scanner;

public class Ex08ForGugu {
	public static void main(String[] args) {
		/*
		 * 구구단 숫자를 입력받아 해당 단을 출력(반복)
		 * 단, 0 입력시 종료
		 * while문 안에 for문 이용
		 */
		Scanner sc = new Scanner(System.in);
		int dan;
		while(true) {
			// 구구단 입력
			System.out.print("단 입력: ");
			dan = sc.nextInt();
			
			// 0일 경우 break
			if(dan == 0) break;
			
			// 예외처리(2~9 아닐 경우 재입력)
//			if(dan < 2 || dan > 9)
			if(!(dan>=2 && dan<=9)) {
				System.out.println("2~9단 범위를 벗어났습니다.");
				continue;
			}
			
			// 제목 출력
			System.out.printf("*** %d단 출력 ***\n", dan);
			
			// for문을 이용해서 구구단 출력
			for(int i=0; i<9; i++) {
				System.out.printf("%d x %d = %2d\n", dan, i+1, dan*(i+1));
			}
		}
		System.out.println("Good Bye~~~");
		
		sc.close();
	}
}
