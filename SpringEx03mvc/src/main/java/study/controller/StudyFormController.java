package study.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

import data.dto.ShopDto;

@Controller
public class StudyFormController {

	@GetMapping("/form1")
	public String goForm1() {

		return "form/testform1";
	}

	@GetMapping("/read1")
	public ModelAndView goResult(
			/*
			 * @RequestParam은 생략가능, 정확히 써주는게 좋다
			 */
			@RequestParam String name, @RequestParam String ipsa,

			// 값이 안넘어 오더라도 오류 제거
			// @RequestParam(required=false) String pageNum

			// 값이 없을 경우 기본값이 10
			@RequestParam(defaultValue = "10") String pageNum) {

		ModelAndView mv = new ModelAndView();

		String result = name + "님의 입사일은 " + ipsa + " 입니다.";
		mv.addObject("pageNum", pageNum);
		mv.addObject("result", result);
		mv.setViewName("result/view1");

		return mv;

	}

	////////////////////////////////////////////////////////////////////

	@GetMapping("/form2")
	public String goForm2() {

		return "form/testform2";
	}

	/* post : 한글깨짐 처리(web.xml)*/
	@PostMapping("/read2")
	public String goRead2(Model model,
			@RequestParam String name,
			@RequestParam String gender,
			@RequestParam("address") String arr
			) 
	{
		model.addAttribute("name", name);
		model.addAttribute("gender", gender);
		model.addAttribute("address", arr);
		
		return "result/view2";
	}
	
	////////////////////////////////////////////////////////////////////

	@GetMapping("/form3")
	public String goForm3() {

		return "form/testform3";
	}

	
	@PostMapping("/read3")
	/* [dto 통째로 읽어오기] 
	 * @ModelAttribute는
	 * model에 'shopDto'(첫글자 소문자)라는 이름으로 저장되어있다.
	 * @ModelAttribute 생략가능
	 */
	public String goRead3(@ModelAttribute ShopDto dto) {
		
//		System.out.println(dto.getSang());
		
		return "result/view3";
	}
}


































