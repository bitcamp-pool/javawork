package day0406;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Ex14FileReader {
	public static void main(String[] args) {
		
		FileReader fr = null;
		BufferedReader br = null; // 줄 단위로 읽는 메서드를 가지고 있음
		
		try {
			fr = new FileReader("../../../bitjava0314/javawork/files/memo1.txt");
			
			br = new BufferedReader(fr); //  줄단위로 읽어오기위해
			while(true) {
				String s = br.readLine();// 한줄 읽기
				if(s == null) // 마지막줄까지 읽으면 null 반환
					break;
				System.out.println(s);
			}
		} catch (FileNotFoundException e) {
			System.out.println("파이일 없어요: " + e.getMessage());
			e.printStackTrace();  // 에러메시지 추적
		} catch (IOException e) { // 예외 추가됨
			e.printStackTrace();
		} finally {
			try {
				if(br != null) br.close();
				if(fr != null) fr.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
