package day0406;

public class Ex10Throws {
	
	// 예외를 던지고...
	public static void test1(String su1, String su2) throws NumberFormatException {
		int sum = Integer.parseInt(su1) * Integer.parseInt(su2);
		System.out.println(su1+ "과" + su2 + "의 곱한 값은 " + sum + "입니다");
	}
	
	public static void main(String[] args) {

		// 예외를 받고... 처리
		try {
			test1("4", "5");
			test1("100", "200");
			test1("백", "삼백");
			test1("2", "3"); // 이 부분 실행 안됨
			
		} catch (NumberFormatException e) {
			System.out.println("문자가 전달됐어요!! :" + e.getMessage());
		}
		
		
		
		
		System.out.println("**정상종료**");
	}
}
