package day0406;

import java.util.Scanner;

@SuppressWarnings("serial")
class ScoreException extends Exception {
	public ScoreException(String msg) {
		super(msg);
	}
}

public class Ex12ScoreException {
	// writeScore(int score)
	// 1~100 사이의 값이 오면 "내 점수는 90점입니다"라고 출력
	// 그 외에는 ScoreException을 강제발생("잘못된 점수 입니다")
	
	public static void writeScore(int score) throws ScoreException {
		if(!(score >= 1 && score <= 100)) { // score<1 || score>100
			throw new ScoreException("잘못된 점수입니다!");
		} else {
			System.out.println("내 점수는 " + score + "점입니다.");
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new  Scanner(System.in);
		String input = "";
		int score = 0;
		while(true) {
			System.out.print("점수를 입력하세요 : ");
            input = sc.nextLine();			
            if(input.equals("q"))
            	break;
			score = Integer.parseInt(input);
			
			try {
				writeScore(score);
				
			} catch (ScoreException e) {
				System.out.println("예외발생 : " + e.getMessage());
			}			
		}
		System.out.println("**** 프로그램 정상 종료 *****");
		sc.close();
	}
}
