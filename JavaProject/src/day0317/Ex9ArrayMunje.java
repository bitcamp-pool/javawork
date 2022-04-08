package day0317;

public class Ex9ArrayMunje {
	public static void main(String[] args) {
		/* [점수에 대한 등수 출력하기]
		 *  	출력양식
		 *  
		 *  	번호	점수	등수
		 *  	--------------------
		 *  	  1	     67      5
		 *  	  2	     89      2
		 *  	  3	     78      4
		 *  	  4	     89      2
		 *  	  5	    100      1
		 */
		int[] score = { 67, 89, 78, 89, 100 };
		int[] rank = new int[5];
        
		// 등수 구하기
		for(int i=0; i<score.length; i++) {
			// 등수는 1부터 시작해서 나보다 잘한 사람이 있을때 마다 1을 더한다.
			rank[i] = 1;
			for(int j=0; j<score.length; j++) {
				if(score[i] < score[j]) {
					// 나보다 잘한 사람이 없으면 1등(초기값)
					rank[i]++;
				}
			}
		}
		
		System.out.println("\t    [성적 출력]\n");
		System.out.println("\t번호\t점수\t등수");
		System.out.println("\t--------------------");
		for(int n=0; n<score.length; n++) {
			System.out.printf("\t%2d\t%3d\t%2d\n", n+1, score[n], rank[n]);
		}
	}
}
