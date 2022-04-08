package day0404;
/**
 * 인자 전달 방식 
 *
 */
class Person {
	String name;
	String addr;
}

public class Ex06CallBy {
	
	public static void changeInt(int a) {
		a = 10;
	}
	
	public static void changeArray(int[] a) {
		a[2] = 25;
	}
	
	public static void changePerson(Person p) {
		p.addr = "제주도";
	}
	
	// String은 클래스타입이지만 값이 전달된다.
	public static void changeString(String s) {
		s = "apple";
	}
	
	public static void main(String[] args) {
		// 값을 , 주소를 보냈을 경우
		int n = 5;
		changeInt(n); // n값 전달(call by value)
		System.out.println(n);
		
		int[] arr = { 1, 5, 10 };
		changeArray(arr); // 주소를 전달, call by reference
		for(int a : arr)
			System.out.println(a);
		
		Person p = new Person();
		p.name = "홍길동";
		p.addr = "서울";
		changePerson(p); // 주소를 전달, call by reference
		System.out.println(p.name + ", " + p.addr );
		
		String s = "orange";
		changeString(s); // 값이 전달되므로 메서드에서 변경된 값이 반영안됨
		System.out.println(s);
		
		
	}
}
