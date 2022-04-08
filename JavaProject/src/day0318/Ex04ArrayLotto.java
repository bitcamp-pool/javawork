package day0318;

public class Ex04ArrayLotto {
	public static void main(String[] args) {
		
		int[] lotto = new int[6];
		/*
		 * [문제] 1~45 중복되지 않는 난수를 배열에 저장 후
		 *        오름차순으로 출력하시오
		 */
		
		// 난수 발생(중복처리) : 다중for
		for(int i=0; i<lotto.length; i++) {
			lotto[i] = (int) (Math.random()*45) + 1;
			for(int j=0; j<i; j++) {
				if(lotto[i] == lotto[j]) {
					i--;
					break;
				}
			}
		}
		// 오름차순 정렬 : 다중 for
		for(int i=0; i<lotto.length-1; i++) {
			for(int j=i+1; j<lotto.length; j++) {
				if(lotto[i] > lotto[j]) {
					int temp = lotto[i];
					lotto[i] = lotto[j];
					lotto[j] = temp;
				}
			}
		}
		// 결과 출력
		for(int i=0; i<lotto.length; i++) {
			System.out.printf("%02d  ", lotto[i]);
		}
	}
}
