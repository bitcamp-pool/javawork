package day0317;

public class Ex5ArrayMunje {
	public static void main(String[] args) {
		
		int[] data = {56, 67, 79, 89, 100};
		int sum = 0; // 합계
		double avg;  // 평균
		
		// for 사용 합계구하기
//		for(int i=0; i<data.length; i++) {
//			sum += data[i];
//		}
		for(int n : data)
			sum += n;
		
		// avg 구하기
		avg = (double)sum / data.length;
		
		// 출력
		System.out.printf("합계 = %5d\n", sum);
		System.out.printf("평균 = %.2f",  avg);
	}
}
