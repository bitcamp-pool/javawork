package day0315;

import java.util.Scanner;

public class Ex09Operator {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int kor;
		String msg;
		
		System.out.print("국어 점수를 입력하세요: ");
		kor = Integer.parseInt(sc.nextLine());
		
		// else if문으로 해보기
		if (kor >= 90)
			msg = "Excellent!!";
		else if (kor >= 80)
			msg = "Good!!";
		else
			msg = "Try!!";
		
		System.out.println(kor + "=> " + msg);
		
		// 조건 연산자로 해보기
		msg = kor >= 90 ? "Excellent~" : kor >= 80 ? "Good~" : "try~";
		System.out.println(kor + "=> " + msg);
		
		sc.close();
	}
}
