package day0404;

public class Ex09VarArgs {
	
	// ...는 같은 타입으로 개수에 상관없이 인자로 받을 수 있으며
	// 배열 타입으로 받는다. (가변인자)
	public static void writeColor(String ...color) {
		System.out.println("총 " + color.length + "개");
		for(String s : color)
			System.out.print(s + ", ");
		System.out.println();
	}
	
	public static void main(String[] args) {
		writeColor();
		writeColor("white");
		writeColor("red", "blue", "black");
		writeColor("red", "orange", "blue", "black", "pink");
		
		System.out.println("*** 아래의 메서드를 만들어 보세요");
		int s = sum(3, 5, 6); // sum은 전달받은 숫자 출력 후 합계를 구해서 리턴
		System.out.println("합계: " + s);
		
		int s2 = sum(10, 20, 30, 67, 77);
		System.out.println("합계: " + s2 );
	}

	public static int sum(int...arr) {
		int total = 0;
		for (int i=0; i<arr.length; i++)
			total += arr[i];
		
		return total;
	}
}
