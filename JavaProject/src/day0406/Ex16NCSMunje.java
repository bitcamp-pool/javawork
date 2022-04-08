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
public class Ex16NCSMunje {
	public static void main(String[] args) {
		
		FileReader fr = null;
		BufferedReader br = null;
		
		int len = 0;	  // 점수 개수
		int total = 0;    // 총점
		double avg = 0.0; // 평균
		String desc = "점수들\n"; 
		
		try {
			fr = new FileReader("../../../bitjava0314/javawork/files/scores.txt");
			br = new BufferedReader(fr);
			
			while(true) {
				String s = br.readLine();
				if(s == null)
					break;
				desc += s + " ";
				len++;
				total += Integer.parseInt(s);
			}
			
			avg = (double)total/len; 
			
			System.out.println(desc);
			System.out.println("총 "    + len + "개");
			System.out.println("총점: " + total);
			System.out.println("평균: " + avg);
			
		} catch (FileNotFoundException e) {
			System.out.println(e.getMessage());
		} catch (IOException ie) {
			ie.printStackTrace();
		} finally {
			try {
				if(br!=null) br.close();
				if(fr!=null) fr.close();
				
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
}
