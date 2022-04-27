package study1;

public class Hello {
	
	private String name;
	private int age;
	
	public Hello() {
		this.name="강호동";
		this.age=20;
	}
	
	public String getInfo() {
		String s = "내 이름은 " + name + "이고 " + age + "세입니다.";
		return s;
	}
}
