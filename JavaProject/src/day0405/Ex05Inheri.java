package day0405;

class Fruit {
	private int danga;
	
	public Fruit() {
		danga = 1000;
	}
	public Fruit(int danga) {
		this.danga = danga;
	}
	public int getDanga() {
		return danga;
	}
}
////////////////////////////////
class Orange extends Fruit {
	private String name;
	
	public Orange() {
		name = "오렌지";
	}
	public Orange(String name){
		// super(); 생략
		this.name = name;
	}
	public Orange(String name, int danga) {
		super(danga); // 부모에 단가 전달
		this.name = name; // 
	}
	public void write() {
		System.out.println("과일명: " + name + ", 단가:" + this.getDanga());
	}
}


public class Ex05Inheri {
	public static void main(String[] args) {
		Orange[] or = new Orange[3];
		or[0] = new Orange();
		or[1] = new Orange("키위");
		or[2] = new Orange("딸기", 3000);
		
		for(Orange e : or) {
			e.write();
		}
	}
}
