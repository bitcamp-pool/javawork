package day0406;

import java.io.FileWriter;
import java.io.IOException;

public class Ex13FileWriter {
	public static void main(String[] args) {
		
		FileWriter fw = null;
		try {
			/* FileWriter(String fileName)
			 * FileWriter(String fileName, boolean append)
			 * D:\bitjava0314\javawork
			 */
			fw = new FileWriter("..\\..\\..\\bitjava0314\\javawork\\files\\memo1.txt", true); // ctrl+1
			fw.write("이름:최지혜\n");
			fw.write("주소: 서울시 강남구\n");
			fw.write("---------------------\n");
			System.out.println("파일을 확인하세요~");
			
		} catch (IOException e) {
			System.out.println(e.getMessage());
		} finally {
			try {
				fw.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
