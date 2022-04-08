package day0407;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Ex02FileReadWrite {
	
	// 상수 선언
	public static final String FILENAME = "../../../bitjava0314/javawork/files/info.txt";
	
	public static void dataAdd(String name, String hp, String addr) {
		// 저장 시 ,로 연결해서 한줄에 저장
		String data = name + "," + hp + "," + addr + "\n";
		
		// 추가모드(append)로 객체 생성
		FileWriter fw = null;
		try {
			fw = new FileWriter(FILENAME, true);
			fw.write(data); // 파일에 데이터 저장
			System.out.println("입력데이터 저장 완료!!\n");
			
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if(fw!=null)
				try {
					fw.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
		}
	}
	
	public static void dataAllWrite() {
		
		FileReader fr = null;
		BufferedReader br = null;
		
		try {
			fr = new FileReader(FILENAME);
			br = new BufferedReader(fr);
			
			System.out.println("\t**[전체 멤버정보]**");
			System.out.println();
			System.out.println("번호\t이름\t핸드폰\t\t주소");
			System.out.println("-------------------------------------------");
			int n = 0;
			while(true) {
				// 파일에서 한 줄 읽기
				String line = br.readLine();
				
				// null일 경우 while문 종료
				if(line == null) break;
				
				// ,로 분리
				String[] info = line.split(",");
				System.out.printf("%d\t%s\t%s\t%s\n", ++n, info[0], info[1], info[2]);
			}
			System.out.println("-------------------------------------------");
			
		} catch (FileNotFoundException e) {
			System.out.println("파일이 존재하지 않습니다.");
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if(br!=null) br.close();
				if(fr!=null) fr.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static void fileDelete() {
		// File 객체로 생성을 해야 삭제 가능
		File file = new File(FILENAME);
		
		// 파일이 실제 존재할 경우만 삭제
		if(file.exists()) {			
			System.out.println("삭제할 파일의 크기: " + file.length());
			file.delete();
			System.out.println("파일을 삭제했습니다.");
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = 0;
		EXIT:
		while(true) {
			System.out.println("1.데이터 추가 2.전체출력 3.파일삭제 4.종료");
			n = Integer.parseInt(sc.nextLine());
		    switch (n) {
			case 1:
			{
				System.out.print("추가할 이름 입력: ");
				String name = sc.nextLine();
				
				System.out.print("추가할 핸드폰 입력: ");
				String hp = sc.nextLine();
				
				System.out.print("추가할 주소 입력: ");
				String addr = sc.nextLine();
				
				dataAdd(name, hp, addr);
				break;
			}
			case 2:
				dataAllWrite();
				break;
			case 3:
				fileDelete();
				break;
			case 4:
//				System.out.println("프로그램을 종료합니다.");
//				System.exit(0);
				break EXIT;
			}
		}
		System.out.println("프로그램을 종료합니다.");
		sc.close();
	}
}
