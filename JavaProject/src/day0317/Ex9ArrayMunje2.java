package day0317;

public class Ex9ArrayMunje2 {
	public static void main(String[] args) {
		int[] lotto = new int[6];
		/*
		 * lotto 배열에 1~45 사이의 난수 6개를 넣은 후 출력하기
		 * 단, 중복 숫자가 있으면 안됨!
		 */
		for(int i=0; i<lotto.length; i++) {
			// 1~45 난수 생성
			lotto[i] = (int)(Math.random()*45) + 1;
			
			for(int j=0; j<i; j++) {
				if(lotto[i] == lotto[j]) {
					i--;   // 인덱스 번호 원래대로 셋팅하기 위해서
					break; // i++ 로 이동
				}
			}
		}
		
		for(int n : lotto)
			System.out.printf("%4d", n);
	}
}
