package day0315;

import java.util.Scanner;

public class Ex05Scanner {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int score;
		String name;
		char blood;
		
//		방법1
//	    System.out.println("점수입력: "); 
//	    score = sc.nextInt(); 
//	    sc.nextLine(); // 버퍼의 엔터를 읽어서 소멸시킨다.
	 
//	    방법2
		System.out.print("점수입력: ");
		score = Integer.parseInt(sc.nextLine()); // 숫자형태가 아닐경우 예외발생
		
		System.out.print("이름입력: ");
		name = sc.nextLine();
		
		System.out.print("혈액형 한글자 입력: ");
		blood = sc.nextLine().charAt(0);
		
		System.out.println("이름   : " + name );
		System.out.println("점수   : " + score );
		System.out.println("혈액형 : " + blood );
		
		sc.close();
	}
}
