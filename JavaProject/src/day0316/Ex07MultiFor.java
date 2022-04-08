package day0316;

public class Ex07MultiFor {
	public static void main(String[] args) {
		/*
		 	★★★★★
			★★★★★
			★★★★★
			★★★★★
			★★★★★
		 */
		for(int i=0; i<5; i++) { // 행
			for(int j=0; j<5; j++) { // 열
				System.out.print('★');
			}
			System.out.println();
		}
		System.out.println("1)--------------------------");
		
		/*
		 	★
			★★
			★★★
			★★★★
			★★★★★
		*/
		for(int i=0; i<5; i++) { // 행
			for(int j=0; j<i+1; j++) { // 열
				System.out.print("★");
			}
			System.out.println();
		}
		System.out.println("2)--------------------------");
		for(int i=0; i<5; i++) { // 행 0,1,2,3,4
			for(int j=0; j<5; j++) { // 열 0,1,2,3,4
				if(i >= j)
					System.out.print("★");
			}
			System.out.println();
		}
		System.out.println("3)--------------------------");
		
		/*
			★★★★★
			★★★★
			★★★
			★★
			★
		*/
		for(int i=0; i<5; i++) { // 행 0,1,2,3,4
			for(int j=5; j>i; j--) { // 열 5,4,3,2,1
				System.out.print("★");
			}
			System.out.println();
		}
		System.out.println("4)--------------------------");
		
		for(int i=0; i<5; i++) { // 행
			for(int j=i; j<5; j++) { // 열 0,1,2,3,4
				System.out.print("★");
			}
			System.out.println();
		}
		System.out.println("5)--------------------------");
		
		/*
		       ★
		      ★★ 
		     ★★★ 
		    ★★★★ 
		   ★★★★★
		 */	
		for(int i=0; i<5; i++) { // 0,1,2,3,4
			for(int j=0; j<5; j++) { // 0,1,2,3,4
				if (i+j>= 4)
					System.out.print("★");
				else
					System.out.print(" ");
			}
			System.out.println();
		}
		System.out.println("6)--------------------------");
		
		for(int i=0; i<5; i++) { // 0,1,2,3,4
			for(int j=i; j<5; j++) { // 0,1,2,3,4
				System.out.print(" ");
			}
			for(int j=1; j<=i; j++) {
				System.out.print("*");
			}
			System.out.println();
		}
		System.out.println("7)--------------------------");
	}
	
	     
}
