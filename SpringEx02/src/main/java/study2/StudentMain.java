package study2;

import org.springframework.context.ApplicationContext;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class StudentMain {
	public static void main(String[] args) {
		
		ApplicationContext context =
				new ClassPathXmlApplicationContext("appContext.xml");
		
		Student stu = (Student) context.getBean("stu");
		
		// toString() 호출
		System.out.println(stu);
		
		// context 사용이 만료된 후
		((ConfigurableApplicationContext) context).close();
	}

}
