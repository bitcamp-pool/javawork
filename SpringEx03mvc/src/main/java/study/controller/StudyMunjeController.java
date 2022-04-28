package study.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

import data.dto.PersonDto;


@Controller
public class StudyMunjeController {
	
	@GetMapping("/form/munje")
	public String goFormMunje() {

		return "form/munjeform";
	}

	
	@PostMapping("/form/result")
	public String goReadMunjeForm(@ModelAttribute PersonDto dto) {
		
//		System.out.println(dto.getName());
		return "result/view5";
	}
}
