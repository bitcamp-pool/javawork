package day0317;

import java.util.Arrays;

public class Ex6ArrayMunje {
	public static void main(String[] args) {
		
		int[] data = { 100, -56, 67, 89, 230, -800, 32, 
				39, 69, 11, -9, 8, 25, 33, 77 };
		int max, min;
		max = min = data[0];
		
//		for(int i=0; i<data.length; i++) {
//			// 최대값
//			if(max < data[i])
//				max = data[i];
//			// 최소값
//			if(min > data[i])
//				min = data[i];
			
//			max = max < data[i] ? data[i] : max;
//			min = min > data[i] ? data[i] : min;
			
//		}
		
//		System.out.printf("최대값: %5d\n", max);
//		System.out.printf("최소값: %5d\n", min);
		
		Arrays.sort(data); // 오름차순 정렬
		for(int n : data)
			System.out.printf("%d, ", n);
		System.out.println();
		max = data[data.length - 1];
		min = data[0];
		System.out.printf("최대값: %5d\n", max);
		System.out.printf("최소값: %5d\n", min);
	}
}
