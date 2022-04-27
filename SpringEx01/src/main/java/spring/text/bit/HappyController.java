package spring.text.bit;

import java.util.Date;
import java.util.List;
import java.util.Vector;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

// 자동으로 bean 생성(어노테이션 이용)
@Controller
@RequestMapping("/board")	// 반복을 피하기 위해
public class HappyController {
	
	@RequestMapping("/list")
	public ModelAndView list1() {
		ModelAndView mview = new ModelAndView();
		
		List<TestDto> list = new Vector<TestDto>();
		
		list.add(new TestDto("홍길동", "011-1111-1111", "서울"));
		list.add(new TestDto("박남정", "011-2222-1111", "제주"));
		list.add(new TestDto("안신혜", "011-3333-1111", "부산"));
		list.add(new TestDto("강호동", "011-4444-1111", "대구"));
		list.add(new TestDto("이영자", "011-5555-1111", "미국"));
		
		// model 에 데이터 저장
		mview.addObject("today", new Date());
		mview.addObject("list", list);
		
		// 포워드 되는  jsp 파일이름 지정
		mview.setViewName("list2");
		
		return mview;
	}
}
