package study2;

public class Student {
	
	private String name;
	private int age;
	private Score score;
	
	public Student(Score score) {
		this.score = score;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public void setAge(int age) {
		this.age = age;
	}
	
	@Override
	public String toString() {
		String s = name + "(" + age + ")님의 점수는 " + score.getScore() + "입니다.";
		return s;
	}

	public String getName() {
		return name;
	}

	public int getAge() {
		return age;
	}
}
