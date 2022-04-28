package study.controller;

import java.util.Date;

import javax.servlet.http.HttpServletRequest;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.servlet.ModelAndView;

// 자동으로 bean으로 등록하기 위해 어노테이션 사용
@Controller
public class Study1Controller {

	@GetMapping("/")
	public String process1(Model model) {
		
		model.addAttribute("message", "오늘은 즐거운 목요일!!!");
		model.addAttribute("today", new Date());
		
		// 포워드(url안바뀜, model 데이터 전달)
		return "hello/study1";
	}
	
	@GetMapping("/go1")
	public ModelAndView process2() {
		
		ModelAndView mv = new ModelAndView();
		mv.addObject("name", "이지아");
		mv.addObject("addr", "강원도 속초");
		
		// 포워드될 파일명
		mv.setViewName("hello/study2");
		return mv;
	}
	
	@GetMapping("/go2/busan/sea")
	public String process3() {
		
		return "hello/study3";
	}
	
	// 여러 요청을 하나의 페이지로 포워딩
	@GetMapping({"/go3", "/go3/jeju", "/go3/seoul"})
	public String process4(HttpServletRequest request, Model model) {
		
		String urlPath  = request.getContextPath();
		String urlPath2 = request.getRequestURI();
		
		System.out.println(urlPath);
		System.out.println(urlPath2);
		/*
		 * /day0428			<--- 프로젝트명 까지만 구하기
		 * /day0428/go3     <--- 현재 url 전체경로 구하기
		 */
		
		model.addAttribute("path", urlPath);
		
		return "hello/study4";
	}
	
	
}



































