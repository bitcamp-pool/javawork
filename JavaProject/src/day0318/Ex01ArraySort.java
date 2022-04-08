package day0318;

public class Ex01ArraySort {
	public static void main(String[] args) {
		/*
		 * 정렬 (selection sort)
		 */
		int[] data = { 3, 5, 1, 4, 2 };
		
		for(int i=0; i<data.length-1; i++) {
			for(int j=i+1; j<data.length; j++) {
				// 기준값(i)이 더 클 경우 서로 바꾼다(오름차순)
				if(data[i] > data[j]) {
//				if(data[i] < data[j]) (내림차순)
					// 임시변수를 이용해서 변수 안의 값만 바꾼다
					int temp = data[i];
					data[i] = data[j];
					data[j] = temp;
				}
			}
		}
		//  출력
		int n = 0;
		for(int element : data) {
			System.out.printf("data[%d] = %d%n", n, element);
			n++;
		}
	}
}
