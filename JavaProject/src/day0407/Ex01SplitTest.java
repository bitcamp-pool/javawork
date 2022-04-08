package day0407;

import java.util.StringTokenizer;

public class Ex01SplitTest {
	public static void main(String[] args) {
		
		String str = "red,green,blue,yellow,pink";
		
		// ,로 문자열을 분리하여 출력하는 방법 2가지
		System.out.println("1. split을 이용하여 분리하는 방법");
		String[] colors = str.split(",");
		for(String c : colors)
			System.out.println(c);
		
		System.out.println();
		
		System.out.println("2. StringTokenizer 클래스를 이용하여 분리하는 방법");
		StringTokenizer st = new StringTokenizer(str, ",");
		System.out.println("분리할 토큰 수: " + st.countTokens());
		// for 반복문 유의
//		for(int i=0; i<st.countTokens(); i++) {
//			st.nextToken();
//			System.out.println(st.countTokens());
//		}
		
		while(st.hasMoreTokens()) { // 읽을 토큰이 있는 동안 반복
			String s = st.nextToken();
			System.out.println(s);
		}
		System.out.println("--------------------------------------------------------");
		
		String text = "TEL 82-02-997-2059, VER 1.0.19";
		
//		StringTokenizer token = new StringTokenizer(text); // 디폴트가 공백
//		StringTokenizer token = new StringTokenizer(text, "-"); // 구분자 설정
//		StringTokenizer token = new StringTokenizer(text, " -"); // 구분자 설정
//		StringTokenizer token = new StringTokenizer(text, "."); // 구분자 설정
		StringTokenizer token = new StringTokenizer(text, " -.,"); // 구분자 설정
		while(token.hasMoreTokens()) {
			System.out.println(token.nextToken());
		}
		
	}
}
