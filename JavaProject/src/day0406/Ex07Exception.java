package day0406;

public class Ex07Exception {
	public static void main(String[] args) {
		
		int[] arr = {4, 6, 7, 8};
		
		for(int i=0; i<=arr.length; i++) {
			// "정상종료" 출력
			try {
				System.out.println(arr[i]); // Index 4 out of bounds for length 4 예외 발생!!				
			}catch(ArrayIndexOutOfBoundsException e) {
//				e.printStackTrace(); //에러메시지 추적해서 확인
				System.out.println("배열오류: " + e.getMessage());
			}
		}
		System.out.println("**정상종료**");
	}
}
