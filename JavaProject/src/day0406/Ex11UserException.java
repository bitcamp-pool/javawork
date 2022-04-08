package day0406;

import java.util.Scanner;

// 사용자 예외 클래스 구현
@SuppressWarnings("serial")
class UserException extends Exception {
	
	public UserException(String msg) {
		super(msg); // 예외의 메시지로 등록
	}
}

public class Ex11UserException {
	
	public static void writeContent(String msg) throws UserException{
		if (msg.contains("바보") || msg.contains("멍청")) {
			throw new UserException("고운말을 씁시다!!!");
		} else {
			System.out.println("메시지: " + msg);
		}
	}
	
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		while(true) {
			System.out.println("아무 문장이나 입력하시오");
			String msg = sc.nextLine();
			
			if(msg.equals("끝"))
				break;
			
			try {
				writeContent(msg); // ~~~ 오류: 예외를 던지는 메서드 호출(예외를 처리해줘야 한다)
				
			} catch (UserException e) {
				System.out.println("오류메시지: " + e.getMessage());
			}
		}
		
		System.out.println("** 정상종료 **");
		sc.close();
	}
}
