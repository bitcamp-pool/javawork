package day0317;

import java.util.Scanner;

public class Ex02Munje {
	public static void main(String[] args) {
//	Ex01Munje 추가기능 구현: 계속 이어서 다른 숫자 맞추기

		Scanner sc = new Scanner(System.in);
		int rnd, cnt, num;
		char ans;

		Exit: while (true) {
			System.out.println("** 게임을 시작합니다 **");
			cnt = 0; // 초기화
			rnd = (int) (Math.random() * 100) + 1; // 1~100 사이의 난수 발생

			while (true) {
				System.out.print(++cnt + ": ");
				num = Integer.parseInt(sc.nextLine());
				if (num > rnd)
					System.out.println("\t" + num + " 보다 작습니다.");
				else if (num < rnd)
					System.out.println("\t" + num + " 보다 큽니다.");
				else {
					System.out.println("*** 맞았어요!! 정답은 " + rnd + "입니다!!");
					System.out.println("*** 계속하려면 y, 그만하려면 n 입력하세요 ***");

					ans = sc.nextLine().charAt(0);
					if (ans == 'Y' || ans == 'y') {
						System.out.println("** 새로운 난수를 발생합니다. **");
						continue Exit; // 바깥 while문의 처음으로 이동한다.
					} else {
						System.out.println("** 프로그램을 종료합니다. **");
						break Exit; // 바깥 while문을 빠져나간다.
					}
				}
			}
		}

		sc.close();
	}
}
