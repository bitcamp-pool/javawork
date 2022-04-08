package day0407;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/* Set 인터페이스의 특징
 * 1. 비순차적
 * 2. 중복데이터를 허용하지 않는다.
 * 3. Set 인터페이스 : 선언가능, 사용은 구현한 HashSet객체로 사용
 */
public class Ex04Set {
	public static void main(String[] args) {
		
		// 제네릭<String> : 문자열만 넣을 수 있다.
		Set<String> set = new HashSet<String>();
		
		// 순서없이 저장
		set.add("apple");
		set.add("orange");
		set.add("apple");
		set.add("banana");
		set.add("orange");
		set.add("kiwi");
//		set.add(100);  not applicable for the arguments (int): String이 아닌 경우 오류 발생
		
		System.out.println(set.size() + "개"); System.out.println();
		
		System.out.println("출력방법 1.");
		for(String s : set)
			System.out.println(s);
		System.out.println();
		
		System.out.println("출력방법 2.");
		Iterator<String> iter = set.iterator();
		while(iter.hasNext()) {
			String s = iter.next();
			System.out.println(s);
		}
		System.out.println();
		
		
	}
}
