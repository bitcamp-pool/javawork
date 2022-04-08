package day0316;

public class Ex09ForGugu {
	public static void main(String[] args) {
		/*
		 * 2단 부터 9단까지 모두 출력
		 * [2단]	[3단]	....   [9단] : 단일 for
		 * 2x1=2    3x1=3   ....   9x1=9 : 다중 for
		 * .
		 * .
		 * 2x9=18   3x9=27  ...    9x9=81
		 */
		
		for(int a=0; a<8; a++) {
			System.out.printf("[%02d단]\t", a + 2);
		}
		System.out.println();
		
		for(int i=0; i<9; i++) { // 9행
			for(int j=0; j<8; j++) { // 8열
				System.out.printf("%dx%d=%02d\t", j+2, i+1, (j+2)*(i+1));
			}
			System.out.println();
		}
	}
}
