package day0406;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/* 
 *  파일 score.txt 에 저장된 점수들을 읽어서 출력후 총 개수와 총점, 평균을 구하시오
	[예시 결과]
	점수들
	67 78 90 98 100 89 47 97
	총 8 개
	총점 : xxx
	평균 : xx.xx
 */
public class Ex15NCSMunje {
	public static void main(String[] args) {
		
		FileReader fr = null;
		BufferedReader br = null;
		List<Integer> scores = new ArrayList<Integer>();
		int total = 0;
		double avg = 0.0;
		String str = "";
		
		try {
			fr = new FileReader("../../../bitjava0314/javawork/files/scores.txt");
			br = new BufferedReader(fr);
			while(true) {
				String s = br.readLine();
				if(s == null)
					break;
				str += s + " ";
				scores.add(Integer.parseInt(s));
			}
			for(int i : scores)
				total += i;
			avg = (double)total/scores.size(); 
			
			System.out.println("점수들\n" + str);
			System.out.println("총 " + scores.size());
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
