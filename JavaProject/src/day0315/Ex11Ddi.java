package day0315;

import java.util.Scanner;

public class Ex11Ddi {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		/* 서기1년:닭(유)띠
		 * 자 축 인 묘 진 사 오 미 신 유 술 해
		 * 04 05 06 07 08 09 10 11 00 01 02 03
		 */
		String[] index = {
				"원숭이",	// 신 
				"닭",		// 유
				"개",		// 술
				"돼지",		// 해
				"쥐",		// 자
				"소",		// 축
				"호랑이",	// 인
				"토끼",		// 묘
				"용",		// 진
				"뱀",		// 사
				"말",		// 오
				"양"		// 미
				};
		int year;
		String ddi;
		
		System.out.print("태어난 해를 입력하시오: ");
		year = Integer.parseInt(sc.nextLine());
		
		if (year % 12 == 0)
			ddi = "원숭이";
		else if (year % 12 == 1)
			ddi = "닭";
		else if (year % 12 == 2)
			ddi = "개";
		else if (year % 12 == 3)
			ddi = "돼지";
		else if (year % 12 == 4)
			ddi = "쥐";
		else if (year % 12 == 5)
			ddi = "소";
		else if (year % 12 == 6)
			ddi = "호랑이";
		else if (year % 12 == 7)
			ddi = "토기";
		else if (year % 12 == 8)
			ddi = "용";
		else if (year % 12 == 9)
			ddi = "뱀";
		else if (year % 12 == 10)
			ddi = "말";
//		else if (year % 12 == 1)
//			ddi = "양";
		else 
			ddi = "양";
		System.out.println(year + "년생은 " + ddi + "띠입니다1."); 

		// 조건 연산자를 이용해서 구하기
		int a = year % 12;
		ddi = (a == 0) ? "원숭이" : (a == 1) ? "닭" :  (a == 2) ? "개" : (a == 3) ? "돼지" :
			  (a == 4) ? "쥐" : (a == 5) ? "소" : (a == 6) ? "범" : (a == 7) ? "토끼" : 
			  (a == 8) ? "용" : (a == 9) ? "뱀" : (a == 10) ? "말" : "양";	  
		System.out.println(year + "년생은 " + ddi + "띠입니다2."); 
		
		// 배열을 이용해서 구하기
		ddi = index[year % 12];
		System.out.printf("당신은 %s 띠입니다3.", ddi);
		
		sc.close();
	}
}
