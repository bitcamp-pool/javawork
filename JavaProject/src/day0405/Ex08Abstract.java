package day0405;

import java.util.Scanner;

/* (문제)
Command 클래스 - process 추상 메서드
Command 로부터 상속받는 클래스 4개
List, Add, Delete, Update

** 메인 클래스에 메서드 추가
public static void process(Command comm){
	comm.process();
}
** 실행시 결과
1.추가  2.수정  3.삭제  4. 출력  5.종료
선택=> 1
 데이타를 추가합니다(Add생성)
 
선택=> 2
 데이타를 수정합니다(Update생성)

선택=> 3
 데이타를 삭제합니다(Delete생성)

선택=> 4
 데이타를 출력합니다(List생성)

선택=> 5
 프로그램을 종료합니다
 */

abstract class Command {
	public abstract void process();
}
class List extends Command {
	@Override
	public void process() {
		System.out.println("데이타를 출력합니다(List생성)");
	}
}
class Add extends Command {
	@Override
	public void process() {
		System.out.println("데이타를 추가합니다(Add생성)");
	}
}
class Delete extends Command {
	@Override
	public void process() {
		System.out.println("데이타를 삭제합니다(Delete생성)");
	}
}
class Update extends Command {
	@Override
	public void process() {
		System.out.println("데이타를 수정합니다(Update생성)");
	}
}

public class Ex08Abstract {
	public static void process(Command comm){
		comm.process();
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		System.out.println("1.추가  2.수정  3.삭제  4. 출력  5.종료");
		while(true) {
			System.out.print("선택=> ");
			int input = Integer.parseInt(sc.nextLine());
			if(input == 5)
				break;
			switch(input) {
				case 1: process(new Add()); break;
				case 2: process(new Update()); break;
				case 3: process(new Delete()); break;
				case 4: process(new List());
			}
		    System.out.println();
		}
		System.out.println("프로그램을 종료합니다.");
		sc.close();
	}
}
