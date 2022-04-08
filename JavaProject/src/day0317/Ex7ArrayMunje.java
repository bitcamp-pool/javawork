package day0317;

import java.util.Scanner;

public class Ex7ArrayMunje {
	public static void main(String[] args) {

		String[] members = { "강소라", "이진", "강호동", "이효리", "손미나"
				, "유재석", "손철수", "유미리", "이제니", "강민" };
		
		String name; // 입력 받을 이름
		int cnt;	 // 인원수 구할 변수
		/*
		 * 문제 : 성을 입력하면 해당 성을 가진 사람을 출력하고
		 * 		  총 몇명인지 출력하기
		 * (예) 
		 * 검색할 성: 이
		 * 		   1: 이진
		 * 		   3: 이효리
		 * 		   8: 이제니
		 * 		   총 3명
		 * 검색할 성: 박
		 * 		박씨성은 없음
		 * 검색할 성: 끝
		 * 	*** 종료합니다 ***
		 * String의 startsWith 사용
		 */
		Scanner sc = new Scanner(System.in);
		while(true) {
			cnt = 0;	// 인원수 초기화
			System.out.print("검색할 성: ");
			name = sc.nextLine();
			if(name.equals("끝"))
				break;
			for(int i=0; i<members.length; i++) {
				if(members[i].startsWith(name)) {
					cnt++;
					System.out.println("\t" + i + ": " + members[i]);
				}
			}
			if(cnt != 0)
				System.out.println("\t" + "총 " + cnt + "명");
			else
				System.out.println("\t" + name + "씨 성은 없음!!");
		}
		System.out.println("*** 종료합니다 ***");
		sc.close();
	}
}
