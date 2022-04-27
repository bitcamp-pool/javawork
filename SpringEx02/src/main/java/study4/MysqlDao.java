package study4;

public class MysqlDao {
	
	public void insertShop(ShopDto dto) {
		System.out.println(dto.getSangpum() + " " 
				+ dto.getPrice() + " 원 짜리 추가");
	}
	
	public void deleteShop(String sang) {
		System.out.println(sang + " 상품 삭제 완료");
	}
}
