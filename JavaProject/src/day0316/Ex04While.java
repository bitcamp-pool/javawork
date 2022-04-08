package day0316;

import java.util.Scanner;

public class Ex04While {
	public static void main(String[] args) {
		/*
		 * 점수를 입력받아 총점, 평균, 입력값 개수를 구하시오
		 * 단, 점수가 1~100 이 아닐 경우 다시 입력(개수 제외)
		 *     점수가 0 일 경우 반복문 종료 후 출력 
		 */
		Scanner sc = new Scanner(System.in);
		int score, total, cnt;
		double avg;
		// 초기화
		total = cnt = 0;
		
		while(true) {
			System.out.print("점수 입력: ");
			score = sc.nextInt();
			if(score == 0)
				break;
			if(score < 0 || score > 100) {
				System.out.println("\t다시 입력하세요!");
				continue; // 조건식으로 이동
			}
			
			total += score;
			cnt++; // 단항일 경우 전위/후위 관계없음
		}
		avg = (double)total / cnt;
		
		System.out.println("개수: " + cnt);
		System.out.println("합계: " + total);
		System.out.println("평균: " + avg);
		
		sc.close();
	}
}
/**
 * Infinity 
 * NaN: Not a Number
 */
