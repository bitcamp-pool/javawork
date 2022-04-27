package study3;

import java.util.ArrayList;
import java.util.List;

public class Person {

	List<String> hobby = new ArrayList<String>();
	String address;
	
	public Person(List<String> hobby) {
		this.hobby = hobby;
	}

	public void setAddress(String address) {
		this.address = address;
	}
	
	public void write() {
		
		System.out.println("나의 주소: " + address);
		
		System.out.println("**취미들**");
		for(String h : hobby) {
			System.out.println(h);
		}
	}
}
