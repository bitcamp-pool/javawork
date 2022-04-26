package spring.text.bit;

import java.util.Date;
import java.util.List;
import java.util.Vector;

import javax.servlet.http.HttpSession;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

/**
 * Handles requests for the application home page.
 */
@Controller
public class HomeController {
	
	@RequestMapping(value="/", method = RequestMethod.GET)// spring4까지
	public String test1(Model model, HttpSession session) {
		
		// request 영역에 저장
		model.addAttribute("message", "Spring Framework Start!!!");
		
		// session 영역에 저장
		session.setAttribute("myid", "angle");
				
		return "result1";
	}
	
	@GetMapping("/form") // spring5 버전부터
	public String goForm(){
		return "form";
	}
	
	@GetMapping("/happy")
	public String goNice(Model model) {
		model.addAttribute("today", new Date());
		return "nice";
	}
	
	@GetMapping("/for")
	public String goFor(Model model) {
		
		List<String> list = new Vector<String>();
		
		list.add("red");
		list.add("green");
		list.add("orange");
		list.add("pink");
		list.add("blue");
		list.add("black");
		list.add("gray");
		list.add("magenta");
		
		model.addAttribute("flowers", list);
		
		return "list";
	}
}











