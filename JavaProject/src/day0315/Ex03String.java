package day0315;

public class Ex03String {
	public static void main(String[] args) {
		String s1 = "Happy";
		String s2 = new String("Apple");
		System.out.println(s1);
		System.out.println(s2);
		
		int a = 5, b = 5;
		System.out.println(a == b);
		
		System.out.println(s1 == s2); // == 객체의 주소 비교
		System.out.println();
		
		// 문자열 비교
		System.out.println(s1.equals("Happy"));
		System.out.println(s1.equalsIgnoreCase("happy"));
		System.out.println(s2.equalsIgnoreCase("aPPle"));
		System.out.println(s1.equals("happy"));
		System.out.println(s1.equals(s2));
		
		// 문자열 길이
		System.out.println(s1.length());
		System.out.println("kor".length());
		
		// 문자열 문자 추출
		char startChar = s1.charAt(0);
		System.out.println(startChar);
		
		// 대소문자 변환
		System.out.println(s1.toUpperCase());
		System.out.println(s2.toLowerCase());
		
		// 특정 문자열 시작/끝 비교
		String s3 = "Have a Nice Day!!";
		System.out.println(s3.startsWith("Have"));  // 문자열의 시작
		System.out.println(s3.endsWith("!"));		// 문자열의 끝
		System.out.println(s3.startsWith("Happy"));
		System.out.println(s3.endsWith("*"));
	}
}
