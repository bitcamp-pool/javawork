package study3;

import java.util.ArrayList;
import java.util.List;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.stereotype.Component;

/* 스프링 설정에 사용되는 클래스라는 의미(자바 Config)
 * <bean class="study3.ApplicationConfig"/>
 * 위 xml 설정 없이 자동으로 bean 등록하려면?
 * @Component : xml에 자동으로 bean을 등록해준다. 
 */
@Configuration
@Component
public class ApplicationConfig {
	
	// 메서드 이름을 id로 인식
	@Bean
	public Person person3() {
		
		List<String> hobby = new ArrayList<String>();
		hobby.add("노래하기");
		hobby.add("춤추기");
		hobby.add("돌아다니기");
		
		Person p = new Person(hobby);
		p.setAddress("미국 LA");
		
		return p;
	}
	
	
}
