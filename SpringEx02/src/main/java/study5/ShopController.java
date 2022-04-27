package study5;

import javax.annotation.Resource;
import org.springframework.stereotype.Component;
import study4.ShopDto;

/*
 *	@Component // shpoController 아이디 이름으로 자동 등록
 *  @Component("myshop") 특정 이름으로 등록
 */
@Component
public class ShopController {
	
	/*
	 * pom.xml 추가
	 * <dependency> 
		 <groupId>javax.annotation</groupId> 
		 <artifactId>javax.annotation-api</artifactId> 
		 <version>1.3.2</version> 
		</dependency>
	 * @Resource : 정확한 id를 등록	
	 * @Autowired  같은 타입을 찾아서 자동주입
	 */
	@Resource(name = "mysqlDao") 
	MysqlDao dao;
	
//	public ShopController(MysqlDao dao) {
//		this.dao = dao;
//	}
	
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
