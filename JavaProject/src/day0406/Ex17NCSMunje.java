package day0406;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/* 
 *  파일 score.txt 에 저장된 점수들을 읽어서 출력후 총 개수와 총점, 평균을 구하시오
	[예시 결과]
	점수들
	67 78 90 98 100 89 47 97
	총 8 개
	총점 : xxx
	평균 : xx.xx
 */
public class Ex17NCSMunje {
	public static void main(String[] args) {
		
		FileReader fr = null;
		BufferedReader br = null;
		
		int cnt = 0;		// 점수 개수
		int sum = 0;    	// 총점
		double avg = 0.0; 	// 평균
		int score; 			// 점수
		
		try {
			fr = new FileReader("../../../bitjava0314/javawork/files/scores.txt");
			br = new BufferedReader(fr);
			
			System.out.println("입력한 점수들");
			while(true) {
				
				String line = br.readLine(); // 예외를 던지는 메서드(예외처리 추가)
				
				// null인 경우 while문 종료
				if(line==null) break;
				
				// 입력한 점수를 계산이 가능한 int로 변환
				// 만약 문자가 섞여 있을 경우 0 점 처리해보자
				try {
					score = Integer.parseInt(line);
				} catch (NumberFormatException e) {
					System.out.printf("....예외발생:%s", e.getMessage());
					score = 0;
				}
//				score = Integer.parseInt(line);
				
				cnt++; // 개수 증가
				sum += score; // 합계 구하기
				System.out.printf("%5d", score);
			}
			// 평균
			avg = (double)sum/cnt;
			System.out.println();
			System.out.println("개수 :" + cnt);
			System.out.println("총점 :" + sum);
			System.out.println("평균 :" + avg);
			
		} catch (FileNotFoundException e) {
			System.out.println("파일을 찾을 수 없어요: " + e.getMessage());
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if(br!=null) br.close();
				if(fr!=null) fr.close();
			} catch (Exception e) {
				
			}
		}
	}
}
