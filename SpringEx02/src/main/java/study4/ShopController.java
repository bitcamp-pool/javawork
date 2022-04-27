package study4;

public class ShopController {
	
	MysqlDao dao;
	
	public ShopController(MysqlDao dao) {
		this.dao = dao;
	}
	
	public void add(String sang, int price) {
		
		ShopDto dto = new ShopDto();
		
		dto.setSangpum(sang);
		dto.setPrice(price);
		
		dao.insertShop(dto);
	}
	
	public void delete(String sang) {

		dao.deleteShop(sang);
	}
}
