package day0317;

public class Ex04Array {
	public static void main(String[] args) {
		
		int[] arr1 = new int[5];
		int[] arr2 = {4, 6, 7, 8, 10};
		System.out.println("arr1 len = " + arr1.length);
		System.out.println("arr2 len = " + arr2.length);
		
		System.out.println("** 초기값 출력 **");
		
		for (int a : arr1)
			System.out.printf("%5d", a);
		
		System.out.println();
		
		for (int a : arr2)
			System.out.printf("%5d", a);
		
		System.out.println("\n-----------------");
		
		System.out.println("arr1에 값 넣기");
		arr1[1] = 6;
		arr1[3] = 23;
		arr1[4] = 31;
		
		for(int i=0; i<arr1.length; i++)
			System.out.printf("%5d", arr1[i]);
		
		System.out.println("");
		
		
	}
}
