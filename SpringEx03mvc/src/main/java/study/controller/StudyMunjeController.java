package study.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.servlet.ModelAndView;

import data.dto.PersonDto;


@Controller
public class StudyMunjeController {
	
	@GetMapping("/form/munje")
	public String goFormMunje() {

		return "form/munjeform";
	}

	
	@PostMapping("/form/result")
	public ModelAndView goResult(@ModelAttribute PersonDto dto) {
		
		ModelAndView mv = new ModelAndView();
		
		// 총점, 평균 계산
		int tot = dto.getJava() + dto.getSpring();
		double avg = tot/2.0;
		mv.addObject("tot", tot);
		mv.addObject("avg", avg);
		
		mv.setViewName("result/view4");
		
		return mv;
	}
}
