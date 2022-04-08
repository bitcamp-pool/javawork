package day0405;

public class Sawon {
	
	private String name;
	private String buseo;
	private int pay;
	private int overtime;
	
	public Sawon(String name, String buseo, int pay, int overtime) {
		this.name = name;
		this.buseo = buseo;
		this.pay = pay;
		this.overtime = overtime;
	}

	// Read Only
	public String getName() {
		return name;
	}

	public String getBuseo() {
		return buseo;
	}

	public int getPay() {
		return pay;
	}

	public int getOvertime() {
		return overtime;
	}
	
	// 초과수당 계산
	public int getTimeSudang() {
		// 5시간 이상은 무조건 10만원
		// 5시간 미만은 시간 * 18000
		if(overtime >= 5)
			return 100000;
		else
			return overtime * 18000;
	}
	
	// 실수령액 반환
	public int getNetPay() {
		return pay + getTimeSudang();
	}
}
