package day0406;

import java.util.Date;

public class Ex09Exception {
	public static void main(String[] args) {
		
		Date date = null;		// 예외 발생되는 경우
//		Date date = new Date(); // 예외 발생 안되는 경우
		int year = 0;
		try {
			year = date.getYear() + 1900; //java.lang.NullPointerException
			
		} catch (Exception e) {
			System.out.println("객체가 생성안됨: " + e.getMessage());
			date = new Date();
			year = date.getYear() + 1900;
		} finally { // 예외 발생 유무 관계없이 실행
			System.out.println("**무조건 실행되는 영역**");
			System.out.println("지금은 " + year + "년도입니다.");
		}
		
		System.out.println("**정상종료**");
	}
}
