package board.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.servlet.ModelAndView;

import board.data.MyCarDao;
import board.data.MyCarDto;

@Controller
public class ListController {

	@Autowired
	MyCarDao dao;
	
	@GetMapping("/")
	public ModelAndView list() {
		
		ModelAndView mv = new ModelAndView();
		
		mv.addObject("message", "스프링 부트 게시판 만들기");
		mv.setViewName("list");
		
		return mv;
	}
	
	@GetMapping("/form")
	public String form() {
		
		return "mycarform";
	}
	
	@PostMapping("/insert")
	public String insert(@ModelAttribute MyCarDto dto) {
		
		dao.insertCar(dto);
		
		/* 목록으로 이동
		 * 해당 매핑주로 url이 바뀜
		 */ 
		return "redirect:/"; 
	}
}








