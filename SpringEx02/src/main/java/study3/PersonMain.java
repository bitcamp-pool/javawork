package study3;

import org.springframework.context.ApplicationContext;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class PersonMain {
	public static void main(String[] args) {
		
		ApplicationContext context =
				new ClassPathXmlApplicationContext("myContext.xml");
		
		Person p1 = (Person) context.getBean("person");
		p1.write();
		System.out.println("------------------------");
		
		Person p2 = (Person) context.getBean("person2");
		p2.write();
		System.out.println("------------------------");
		
		// 자바 클래스 설정 방식(xml 수정필요)
		Person p3 = (Person) context.getBean("person3");
		p3.write();
		System.out.println("------------------------");
		
		// context 사용이 만료된 후
		((ConfigurableApplicationContext) context).close();		
	}
}
