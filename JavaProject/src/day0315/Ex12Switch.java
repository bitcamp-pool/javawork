package day0315;

import java.util.Scanner;

public class Ex12Switch {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n;
		System.out.print("n? ");
		n = sc.nextInt();
		
		switch (n) {
		case 1:
			System.out.println("One!!");
			break;
		case 2:
			System.out.println("Two!!");
			break;
		case 3:
			System.out.println("Three!!");
			break;
		default:
			System.out.println("1, 2, 3 제외!!");
		}
		
		sc.nextLine();
		
		String s;
		System.out.print("노랑, 빨강, 파랑 중 입력: ");
		s = sc.nextLine();
		switch (s) {
		case "노랑":
			System.out.println("노랑색은 희망의 색!!!"); break;
		case "빨강":
			System.out.println("빨강색은 정렬의 색!!!"); break;
		case "파랑":
			System.out.println("파랑색은 사랑의 색!!!"); break;
		default:
			System.out.println("모든색은 아름다워요!!!");
		}
		
		sc.close();
	}
}
