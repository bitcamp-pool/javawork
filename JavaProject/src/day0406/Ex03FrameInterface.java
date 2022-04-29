package day0406;

import java.awt.Button;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

// 인터페이스 연습

public class Ex03FrameInterface extends Frame implements WindowListener, ActionListener {
	private static final long serialVersionUID = 1L;
	Button btn;
	
	// 생성자
	public Ex03FrameInterface() {
		super("Hello"); // 프레임 생성자
		this.setBounds(300, 100, 300, 300);
		this.addWindowListener(this);// 윈도우 이벤트
		this.setLayout(new FlowLayout()); // 레이아웃 변경
		
		btn = new Button("Click");
		this.add(btn);
		btn.addActionListener(this);//버튼 이벤트 발생
		this.setVisible(true);
	}
	
	public static void main(String[] args) {
		new Ex03FrameInterface(); // 생성자 호출
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		System.out.println("버튼 클릭했어요!!!");
		
	}

	@Override
	public void windowOpened(WindowEvent e) {
		
	}

	@Override
	public void windowClosing(WindowEvent e) {
		System.exit(0); // 윈도우 x 클릭 시 호출(시스템 종료)
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
