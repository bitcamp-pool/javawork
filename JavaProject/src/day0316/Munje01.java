package day0316;

import java.util.Scanner;

/**
 * 1부터 100사이의 난수를 변수 rnd에 저장 후 
 * 그 숫자를 알아맞추는 프로그램을 작성하시오 
 * while문, random 메서드 사용 
 * (예)
 * 임의의 난수가 76이라고 가정 
 * (앞에 입력 카운트 출력) 
 * 1 : 56 
 * 	   56보다 큽니다. 
 * 2 : 65 
 *     65보다 큽니다. 
 * 3 : 78 
 *     78보다 작습니다. 
 * 4 : 76 맞았어요!!! 정답은 76입니다.(rnd값 출력)
 * 
 * 단, 10회 이내에 못맞출 경우 "시간초과!!" 출력 후 프로그램 종료
 */
public class Munje01 {
	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		int num;
		int rnd = (int) (Math.random() * 100) + 1;
		int count = 0;

		while (true) {
			
			System.out.printf("%02d : ", ++count);
			num = sc.nextInt();
			
			if (rnd > num) {
				System.out.printf("\t%d보다 큽니다.\n", num);
			} else if (rnd < num) {
				System.out.printf("\t%d보다 작습니다.\n", num);
			} else {
				System.out.printf("\t맞습니다!!! 정답은 %d입니다.\n", num);
				break;
			}
			
			if (count >= 10) {
				System.out.println("\t시간초과!! 종료합니다.");
				break;
			}
		}
		
		sc.close();
	}
}
