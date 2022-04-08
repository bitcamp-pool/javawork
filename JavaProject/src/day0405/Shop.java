package day0405;

/* DAO(Data Access Object)   : 데이터베이스의 data에 접근하기 위한 객체
 * DTO(Data Transfer Object) : 데이터베이스 레코드의 데이터를 매핑하기 위한 객체  
 * VO(Value Object) : DTO와 혼용, 값 오브젝트로써 값을 위해 쓰인다.                            
 */ 
public class Shop {
	
	private String sangpum;
	private int su;
	private int dan;
	
	public Shop() {
		this("새우깡", 1, 1300); // this() 무조건 첫줄
	}

	public Shop(String sangpum) {
		this(sangpum, 1, 500);
	}
	
	public Shop(String sangpum, int su, int dan) {	
		this.sangpum = sangpum;
		this.su = su;
		this.dan = dan;
	}
	
	public String getSangpum() {
		return sangpum;
	}

	public void setSangpum(String sangpum) {
		this.sangpum = sangpum;
	}

	public int getSu() {
		return su;
	}

	public void setSu(int su) {
		this.su = su;
	}

	public int getDan() {
		return dan;
	}

	public void setDan(int dan) {
		this.dan = dan;
	}
	
	// 3개의 멤버값을 한꺼번에 변경하고자 할 경우
	public void setData(String sangpum, int su, int dan) {
		this.setSangpum(sangpum);
		this.setSu(su);
		this.setDan(dan);
	}
	
	// 수량과 단가를 곲한 값을 반환하는 메서드
	public int getResult() {
		return su * dan;
	}
}
