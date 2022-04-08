package test;

import day0404.Ex01Object;

public class Hello {
	public static void main(String[] args) {
		// 접근지정자가 public이므로 객체 생성 가능
		Ex01Object ex1 = new Ex01Object();
		
		// 멤버가 public일때 가능
		System.out.println(ex1.score); 
		System.out.println(Ex01Object.jungdap);
		
		// Apple a = new Apple(); class가 public이 아니므로...
	}
}
