package study1;

import org.springframework.context.ApplicationContext;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class HelloMain {
	
	public static void main(String[] args) {
		
		// 기존 방식으로 생성
		Hello h1 = new Hello();
		System.out.println(h1.getInfo());
		
		Hello h2 = new Hello();
		System.out.println(h2.getInfo());
		
		System.out.println("**주소비교**");
		System.out.println(h1.hashCode() + " : " + h2.hashCode());
		
		
		System.out.println("**스프링 방식**");
		
		ApplicationContext context =
				new ClassPathXmlApplicationContext("appContext.xml");
		
		// 반환타입이 Object : 형변환 필요
		Hello h3 = (Hello)context.getBean("hello"); 
		System.out.println(h3.getInfo());
		
		// 형변환 불필요 : Hello.class 타입 지정
		Hello h4 = context.getBean("hello", Hello.class);
		System.out.println(h4.getInfo());
		
		/* 스프링에서 bean으로 생성시
		 * 주소가 모두 같다(Singleton 객체)
		 * <bean id="hello" class="study1.Hello" 디폴트가 scope="singleton"/>
		 */
		System.out.println("**주소비교**");
		System.out.println(h3.hashCode() + " : " + h4.hashCode());
		
		// context 사용이 만료된 후
		((ConfigurableApplicationContext) context).close();
	}
}

