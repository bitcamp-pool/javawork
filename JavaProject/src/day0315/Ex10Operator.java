package day0315;

import java.util.Scanner;

public class Ex10Operator {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int java, html, oracle;
		
		// 3과목의 점수를 입력받아 합계와 평균(소수2자리)을 출력
		// 과락(40점 미만)이 없고 평균 60 이상이면 "합격"
		
		int sum;
		double avg;
		String msg;
		
		System.out.print("3과목의 점수를 차례대로 입력하시오: ");
		java = sc.nextInt();
		html = sc.nextInt();
		oracle = sc.nextInt();
		
		// 합계, 평균 구하기
		sum = java + html + oracle;
		avg = sum / 3.0;
		
		System.out.println("총점 : " + sum);
		System.out.printf("평균 : %6.2f\n", avg);
		
		// 조건
		boolean result = java >= 40 && html >= 40 && oracle >= 40 && avg >= 60;
		
		if(result)
			msg = "합격";
		else 
			msg = "불합격";
		System.out.println("결과: " + msg);
		
		msg = result ? "합격~" : "불합격~";
		System.out.println("결과: " + msg);
		
		sc.close();
	}
}
