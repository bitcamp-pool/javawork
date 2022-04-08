package day0407;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

/* Map 인터페이스의 특징
 * Key와 Value를 매핑하는 객체
 * Key는 절대 중복불가
 * 각 Key는 1개의 Value만 매핑
 * 정렬의 기준이 없다(키는 set 구조)
 * get(Object key)
 * keySet()
 * put(K key, V value)
 */
public class Ex05Map {
	public static void main(String[] args) {
		
		Map<String, String> map = new HashMap<String, String>();
		
		// map에 k, v 의 쌍으로 데이터 추가
		map.put("name", "김태희");
		map.put("age",  "32");
		map.put("addr", "서울");
		map.put("name", "이소라"); // 같은 key일 경우 덮어 쓰기 때문에 중복키가 발생하지 않는다.
		
		System.out.println(map.size() + "개");
		
		System.out.println("**출력1 : key값으로 얻고자 할 경우");
		System.out.println("이름: "   + map.get("name"));
		System.out.println("나이: "   + map.get("age"));
		System.out.println("주소: "   + map.get("addr"));
		System.out.println("형액형: " + map.get("blood")); // 해당 key가 없을 경우? null
		System.out.println("-------------------------------------------------------------");
		
		System.out.println("**출력2: key를 먼저 전체를 얻은 후 해당 v 값을 출력");
		// key는 Set타입 : 비순차적 중복(x)
		Set<String> keys = map.keySet();
		for(String key : keys) {
			String v = map.get(key);
			System.out.println(key + ":" + v);
		}
	}
}
