package day0317;

import java.util.Scanner;

public class Ex8ArrayMunje {
	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		String[] members = { "강소라", "이진", "강호동", "이효리", "손미나"
				, "유재석", "손철수", "유미리", "이제니", "강민", "이진" };
		String name; // 입력 받을 이름
		int cnt; // 인원수
		/*
		 * 검색할 이름 : 이진
		 * 		이진님은 2번째에 있습니다.
		 * 검색할 이름 : 이준희
		 * 		이준희님은 명단에 없습니다.
		 * 검색할 이름 : exit
		 * 		** 검색을 종료합니다 **
		 */
		
		while(true) {
			cnt = 0;
			System.out.print("검색할 이름 : ");
			name = sc.nextLine();
			if(name.equalsIgnoreCase("exit"))
				break;
			for(int i=0; i<members.length; i++) {
				if(name.equals(members[i])) {
					System.out.println("\t" + name + "님은 " + (i+1) + "번째에 있습니다.");
					cnt++;
				}
			}
			if(cnt == 0) {
				System.out.println("\t" + name + "님은 명단에 없습니다.");
			}
		}
		System.out.println("\t" + "검색을 종료합니다.");
		sc.close();
	}
}
