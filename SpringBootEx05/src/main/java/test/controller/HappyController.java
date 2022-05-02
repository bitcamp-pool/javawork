package test.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

/*
 * Rest API 전용 컨트롤러
 * https://meetup.toast.com/posts/92
 */
@RestController
public class HappyController {
	
	/* Rest 전용 컨트롤러이므로 @ResponseBody를
	 * 안써도 json으로 반환
	 */
	
	@GetMapping("/happy1")
	public TestDto happy1() {
		
		TestDto dto = new TestDto();
		
		dto.setName("이미자");
		dto.setHp("010-2323-4545");
		dto.setAddr("서울시 영등포구");
		
		return dto;
	}
}
