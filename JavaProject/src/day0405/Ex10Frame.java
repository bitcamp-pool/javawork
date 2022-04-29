package day0405;

import java.awt.Color;
import java.awt.Frame;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

public class Ex10Frame extends Frame implements WindowListener {	
	private static final long serialVersionUID = 1L;

	public static void main(String[] args) {
		
		new Ex10Frame(); //디폴트 생성자 호출
	}
    
	public Ex10Frame() {
		super("안녕하세요");
		this.setBounds(300, 100, 300, 300);
		this.setBackground(Color.pink);
		this.addWindowListener(this);
		this.setVisible(true);
	}
	
	// Source>Override/Implement Methods 자동생성 창에서 
	@Override
	public void windowOpened(WindowEvent e) {
		
	}

	@Override
	public void windowClosing(WindowEvent e) {
		System.out.println("윈도우 종료");
		System.exit(0); // 프로그램 종료
	}

	@Override
	public void windowClosed(WindowEvent e) {
		
	}

	@Override
	public void windowIconified(WindowEvent e) {
		
	}

	@Override
	public void windowDeiconified(WindowEvent e) {
		
	}

	@Override
	public void windowActivated(WindowEvent e) {
		
	}

	@Override
	public void windowDeactivated(WindowEvent e) {
		
	}

}
