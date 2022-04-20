package mysql.data;

public class ShopDto {
	
	private String num;
	private String sangpum;
	private String photo;
	private int price;
	private String color;
	private int cnt;
	private String ipgoday;
	
	public String getNum() {
		return num;
	}
	public void setNum(String num) {
		this.num = num;
	}
	public String getSangpum() {
		return sangpum;
	}
	public void setSangpum(String sangpum) {
		this.sangpum = sangpum;
	}
	public String getPhoto() {
		return photo;
	}
	public void setPhoto(String photo) {
		this.photo = photo;
	}
	public int getPrice() {
		return price;
	}
	public void setPrice(int price) {
		this.price = price;
	}
	public String getColor() {
		return color;
	}
	public void setColor(String color) {
		this.color = color;
	}
	public int getCnt() {
		return cnt;
	}
	public void setCnt(int cnt) {
		this.cnt = cnt;
	}
	public String getIpgoday() {
		return ipgoday;
	}
	public void setIpgoday(String ipgoday) {
		this.ipgoday = ipgoday;
	}
}
