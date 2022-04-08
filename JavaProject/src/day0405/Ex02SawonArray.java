package day0405;

import java.util.Scanner;

public class Ex02SawonArray {
	
	Scanner sc;
	int inwon;
	Sawon[] sawon;
	
	public Ex02SawonArray() {
		sc = new Scanner(System.in);
	}
	// 키보드로 인원수를 입력받아 sawon을 배열 할당 후 입력받기
	public void dataInwon() {
		System.out.println("인원수를 입력하세요 ");
		inwon = Integer.parseInt(sc.nextLine());
		
		// 사원 배열 할당
		sawon = new Sawon[inwon];
		
		// 배열 개수만큼 입력받아서 생성자 호출하기
		for(int i=0; i<sawon.length; i++) {
			System.out.println("사원명: ");
			String name = sc.nextLine();
			System.out.println("소속부서명: ");
			String buseo = sc.nextLine();
			System.out.println("기본급: ");
			int pay = Integer.parseInt(sc.nextLine());
			System.out.println("초과근무시간: ");
			int time = Integer.parseInt(sc.nextLine());
			
			// Sawon 생성
			sawon[i] = new Sawon(name, buseo, pay , time);
			System.out.println();
		}
	}
	// 제목
	public static void showTitle() {
		System.out.println("--------------------------------------------------------------------------------------");
		System.out.println("번호\t사원명\t부서명\t기본급\t초과시간\t시간수당\t실수령액");
		System.out.println("--------------------------------------------------------------------------------------");
	}
	
	// 출력
	public void dataWrite() {
		for(int i=0; i<sawon.length; i++) {
			System.out.println((i+1) + "\t" + sawon[i].getName() + "\t" +
					sawon[i].getBuseo() + "\t" + sawon[i].getPay() + "\t" +
					sawon[i].getOvertime() + "\t" + sawon[i].getTimeSudang()
					+ "\t" + sawon[i].getNetPay());
		}
	}
	
	public static void main(String[] args) {
		// 메서드 호출부분만 직접 코딩해 보세요
		// 입력 후 제목 출력 그리고 데이터 출력(순서)
		
		Ex02SawonArray ex = new Ex02SawonArray();
		ex.dataInwon();
//		Ex02SawonArray.showTitle(); // 클래스명 생략가능
		showTitle();
		ex.dataWrite();
	}
}
