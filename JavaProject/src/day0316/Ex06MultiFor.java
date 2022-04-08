package day0316;

public class Ex06MultiFor {
	public static void main(String[] args) {
		for(int i = 0; i < 3; i++) {
			System.out.println("Hello!");
			for(int j = 0; j < 4; j++) {
				System.out.print("\tKitty!!");
			}
			System.out.println("********");
		}
		System.out.println("------------------------------------------------------------");
		
		for(int i = 0; i < 3; i++) {
			System.out.println("Hello!");
			for(int j = 0; j < 4; j++) {
				System.out.print("\tKitty!!");
				if(j < 2)
					break;
			}
			System.out.println("********");
		}
		System.out.println("------------------------------------------------------------");
		
		Loop: // 레이블(label)
		for(int i = 0; i < 3; i++) {
			System.out.println("Hello!");
			for(int j = 0; j < 4; j++) {
				System.out.print("\tKitty!!");
				if(j < 2)
					break Loop; // break 레이블 위치로 빠져나온다.
			}
			System.out.println("********");
		}
		System.out.println("------------------------------------------------------------");
	}
}
