package day0315;

public class Ex06Operator {
	public static void main(String[] args) {
		System.out.println("***증감연산자 연습***");
		int a=5, b=5, x, y;
		x=a++; // 후치증감
		y=++b; // 전치증감
		
		System.out.println(a+","+b);
		System.out.println(x+","+y);
		
		a=b=x=3;
		y = ++a + b-- * ++x;  
		//   4  +  3  *  4
		
		System.out.println(y);
		
		a=3;
		System.out.println(a++);
		System.out.println(++a);
		
		System.out.println("***대입연산자 연습***");
		a = 5;
		a += 3;
		System.out.println(a); // 8
		a *= 5;
		System.out.println(a); // 40
		a -= 2;
		System.out.println(a); // 38
		a /= 3;
		System.out.println(a); // 12
		a %= 5;
		System.out.println(a); // 2
	}
}
