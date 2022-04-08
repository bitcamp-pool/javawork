package day0315;

import java.util.Scanner;

public class Ex04Scanner {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String msg = "";
		System.out.print("당신의 이름을 입력하세요: ");
		msg = sc.nextLine(); // 입력한 한줄을 통째로 읽어온다.  엔터키 기준
//		msg = sc.next(); 공백기준
//		System.out.println("내 이름은 " + msg + "입니다.");
//		msg = sc.next();
//		System.out.println("내 이름은 " + msg + "입니다.");
		
		int age;
		System.out.print("당신의 나이는? ");
		age = sc.nextInt();
		System.out.println(msg + "님의 나이는 " + age + "세입니다.");
		sc.close();
	}	
}
