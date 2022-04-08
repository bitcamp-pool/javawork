package day0318;

import java.util.Scanner;

public class Ex05ArrayLotto {
	public static void main(String[] args) {
		/*
		 * [문제]
		 * 금액을 입력하면 금액에 해당하는 횟수만큼 로또 숫자 출력 
		 * 1~45 중복되지 않는 난수를 배열에 저장 후
		 * 오름차순으로 출력하시오
		 * (예)
		 * 로또 구입금액 입력: 3000 
		 * 1회 : 05 08 21 24 25 27 
		 * 2회 : 14 18 19 24 35 43 
		 * 3회 : 05 07 20 23 36 42
		 */
		Scanner sc = new Scanner(System.in);
		int[] lotto = new int[6];
		int money;
		
		System.out.print("로또 구입금액 입력: ");
		money = sc.nextInt();
		if(money < 1000) {
			System.out.println("** 금액이 부족하므로 프로그램을 종료합니다 **");
			sc.close();
			return; // 메서드 안에서 return 문: 현재 메인함수 종료
		}
		
		for(int m=0; m<money/1000; m++) {
			System.out.print(m+1 + "회 : ");
			// 난수 발생(중복처리) : 다중for
			for(int i=0; i<lotto.length; i++) {
				lotto[i] = (int) (Math.random()*45) + 1;
				for(int j=0; j<i; j++) {
					if(lotto[i] == lotto[j]) {
						i--;
						break;
					}
				}
			}
			// 오름차순 정렬 : 다중 for
			for(int i=0; i<lotto.length-1; i++) {
				for(int j=i+1; j<lotto.length; j++) {
					if(lotto[i] > lotto[j]) {
						int temp = lotto[i];
						lotto[i] = lotto[j];
						lotto[j] = temp;
					}
				}
			}			
			// 결과 출력
			for(int i=0; i<lotto.length; i++) {
				System.out.printf("%02d  ", lotto[i]);
			}
			System.out.println();
		}
		sc.close();
	}
}
