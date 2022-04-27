package study5;

import org.springframework.stereotype.Component;

import study4.ShopDto;

@Component // 자동으로 bean 등록(클래스명이 id로 등록:단, 첫 글자는 소문자로)
public class MysqlDao {
	
	public void insertShop(ShopDto dto) {
		System.out.println(dto.getSangpum() + " " 
				+ dto.getPrice() + " 원 짜리 추가");
	}
	
	public void deleteShop(String sang) {
		System.out.println(sang + " 상품 삭제 완료");
	}
}
