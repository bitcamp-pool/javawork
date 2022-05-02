package test.controller;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class HelloController {
	
	@GetMapping("/hello1")
	@ResponseBody // 리턴 타입이  json 타입으로 반환
	public String hello1() {
		return "SpringBoot Start!";
	}
	
	@GetMapping("/hello2")
	@ResponseBody
	public Map<String, String> hello2(){
		Map<String, String> map = new HashMap<>();
		map.put("name", "한가인");
		
		return map;
	}
	
	@GetMapping("/hello3")
	@ResponseBody
	public List<TestDto> hello3(){
		
		List<TestDto> list = new Vector<>();
		
		TestDto dto1 = new TestDto();
		dto1.setName("이영자");
		dto1.setHp("011-111-1234");
		dto1.setAddr("서울시 강남구");
		list.add(dto1);
		
		TestDto dto2 = new TestDto();
		dto2.setName("한지혜");
		dto2.setHp("011-222-1234");
		dto2.setAddr("제주시 애월읍");
		list.add(dto2);
		
		return list;
	}
}
















