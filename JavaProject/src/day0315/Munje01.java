package day0315;

import java.util.Scanner;

/**
상품명과 갯수, 금액을 입력받아 
계산해야 할 총 금액을 출력,
만약 5개 이상일 경우 
총금액의 10%를 할인한 금액으로 출력하시오.
(예)
상품명 : 사과
수량   : 6
단가   : 1000
총 금액은 10% 할인한 5400원 입니다.
 */
public class Munje01 {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
//		DecimalFormat df = new DecimalFormat("#,###");
		
		// 상품명
		String product = "";
		// 갯수
		int count = 0;
		// 금액
		int price = 0;
		// 총금액
		int account = 0;
		
		System.out.print("상품명: ");
		product = sc.nextLine();
		
		System.out.print("수량: ");
		count = Integer.parseInt(sc.nextLine());
		
		System.out.print("단가: ");
		price = Integer.parseInt(sc.nextLine());
		
		account = count * price;
		
		if (count >= 5) {
			account = (int) (account * 0.9);
			System.out.printf("구입한 %s의 총 금액은 10%% 할인한 %d원입니다.", product, account);
		}
		else {
			System.out.printf("구입한 %s의 총 금액은 %d원입니다.", product, account);
		}
		
		sc.close();
	}
}
