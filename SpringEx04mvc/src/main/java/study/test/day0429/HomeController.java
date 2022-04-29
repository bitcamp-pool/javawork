package study.test.day0429;


import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;


/**
 * Handles requests for the application home page.
 */
@Controller
public class HomeController {
	
	@GetMapping("/")
	public String home() {
		
		return "myview/view1";
	}
	
	@GetMapping("/shop/{state}/{num}")
	public String result(
			@PathVariable String state,
			@PathVariable String num,
			Model model
			) 
	{
		System.out.println(state);
		System.out.println(num);
		
		model.addAttribute("state", state);
		model.addAttribute("num", num);
		
		return "myview/result2";
	}
}












