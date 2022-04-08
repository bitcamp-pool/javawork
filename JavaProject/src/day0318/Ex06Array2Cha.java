package day0318;

public class Ex06Array2Cha {
	public static void main(String[] args) {
		// 2차원 배열은 행과 열로...
		// 2행3열
		int[][] arr = new int[2][3];
		System.out.println("행의 개수: " + arr.length);
		System.out.println("0 행의 열의 개수: " + arr[0].length);
		System.out.println("1 행의 열의 개수: " + arr[1].length);
		System.out.println();
		
		for(int i=0; i<arr.length; i++) {
			for(int j=0; j<arr[i].length; j++) {
				System.out.printf("[%d][%d]:%2d\t", i, j, arr[i][j]);
			}
			System.out.println();
		}
		System.out.println();
		/*
		 * 값 넣기
		 */
		arr[0][0] = 10;
		arr[1][1] = 15;
		arr[1][2] = 30;

		for(int i=0; i<arr.length; i++) {
			for(int j=0; j<arr[i].length; j++) {
				System.out.printf("[%d][%d]:%2d\t", i, j, arr[i][j]);
			}
			System.out.println();
		}
	}
}
