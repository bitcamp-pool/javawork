package day0414;


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.SimpleDateFormat;
import java.util.Scanner;

public class Ex02_OracleSwan {
	
	static final String DRIVER = "oracle.jdbc.driver.OracleDriver";
	static final String URL = "jdbc:oracle:thin:@localhost:1521:xe"; // xe, ORCL
	
	Scanner sc = new Scanner(System.in);
	
	// 생성자
	public Ex02_OracleSwan() {
		try {
			Class.forName(DRIVER);
			System.out.println("오라클 드라이버 성공!");
		} catch (ClassNotFoundException e) {
			System.out.println("오라클 드라이버 실패!:"+e.getMessage());
		}
	}
	
	public int getMenu() {
		System.out.println("** 메뉴선택 **");
		System.out.println("1.사원추가  2.전체사원출력 3.사원검색 4.부서별 분석 5.종료");
		int n = Integer.parseInt(sc.nextLine());
		return n;
	}
	
	public void sawonInsert() {
		Connection conn = this.getConnection();
		Statement stmt = null;
		
		System.out.print("사원명: ");
		String name = sc.nextLine();
		
		System.out.print("부서명(홍보부, 인사부, 교육부): ");
		String buseo = sc.nextLine();
		
		System.out.print("기본급: ");
		int gibon = Integer.parseInt(sc.nextLine());
		
		System.out.print("수당: ");
		int sudang = Integer.parseInt(sc.nextLine());
		
		String sql = "insert into sawon values (seq_bit.nextval, '" + name +
				"', '" + buseo + "', " + gibon + ", " + sudang + ", sysdate)";
//		insert into sawon values (seq_bit.nextval, '이기자', '홍보부', 350, 80, sysdate)		
//		System.out.println(sql); 확인
		
		try {
			stmt = conn.createStatement();
			// sql 문을 실행
			stmt.execute(sql);
			
			System.err.println("DB에 데이터가 추가되었어요!!");
			
		} catch (SQLException e) {
			System.out.println("insert 오류: " + e.getMessage());
		} finally {
			try {
				if(stmt != null) stmt.close();
				if(conn != null) conn.close();
			} catch (Exception e2) {
			}
		}
	}
	
	public void sawonSearch() {
		System.out.print("검색할 이름이나 성을 입력: ");
		String searchName = sc.nextLine();
	    String sql =  "SELECT num, name, buseo, gibon, sudang, gibon + sudang total, "
	    			+ "TO_CHAR(writeday, 'yyyy-MM-dd hh:mm') writeday "
	    			+ "FROM SAWON WHERE name LIKE '%" + searchName + "%'";
	    Connection conn = null;
	    Statement stmt = null;
	    ResultSet rs = null;
	    
	    conn = this.getConnection();
	    try {
			stmt=conn.createStatement();
			rs = stmt.executeQuery(sql);
			System.out.println("\t** " + searchName + " 으로 검색 **");
			System.out.println();
			System.out.println("번호\t이름\t부서\t기본급\t수당\t총급여\t등록일");
			while(rs.next()) {
				System.out.println(
						  rs.getString("num")		+ "\t"
						+ rs.getString("name") 		+ "\t"
						+ rs.getString("buseo") 	+ "\t"
						+ rs.getInt("gibon") 		+ "\t"
						+ rs.getInt("sudang") 		+ "\t"
						+ rs.getInt("total") 		+ "\t"
						+ rs.getString("writeday") 	+ "\t"
						);
			}
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
				if(conn != null) conn.close();
			} catch (Exception e) {
			}
		}
	}
	
	public void sawonBuseoGroup() {
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs = null;
		String sql =  "SELECT buseo, round(avg(gibon + sudang), 0) pay "
					+ "FROM SAWON "
					+ "GROUP BY BUSEO";
		
		conn = this.getConnection();
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(sql);
			System.out.println("** 부서별 평균급여 **");
			System.out.println("부서명\t평균급여");
			
			while(rs.next()) {
				String buseo = rs.getString("buseo");
				int pay = rs.getInt("pay");
				
				System.out.println(buseo + "\t" + pay);
			}
		} catch(SQLException e){
			e.printStackTrace();
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
				if(conn != null) conn.close();
			} catch (Exception e) {
			}
		}
	}
	
	public void sawonAllWrite() {
		Connection conn = this.getConnection();
		Statement stmt = null;
		ResultSet rs = null;
		String sql = "select * from sawon order by name"; // 이름순
		
		try {
			stmt = conn.createStatement();
			rs = stmt.executeQuery(sql);
			
			// 제목출력
			System.out.println("번호\t사원명\t부서명\t기본급\t수당\t총급여\t등록일");
			
			// 데이터 출력
			while(rs.next()) {
				
				// 열번호로 가져오기
				
//				int num = rs.getInt(1);
//				String name = rs.getString(2);
//				String buseo = rs.getString(3);
//				int gibon = rs.getInt(4);
//				int sudang = rs.getInt(5);
//				int total = gibon + sudang;
//				java.sql.Timestamp ts = rs.getTimestamp(6);
				
				// 컬럼명으로 가져오기
				int num = rs.getInt("num");
				String name = rs.getString("name");
				String buseo = rs.getString("buseo");
				int gibon = rs.getInt("gibon");
				int sudang = rs.getInt("sudang");
				int total = gibon + sudang;
				java.sql.Timestamp ts = rs.getTimestamp("writeday");
				
				// 날짜를 문자열로 변환
//				SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm"); // 날짜 데이터를 문자열로...
				SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd a hh:mm");
				
				System.out.println(num + "\t" + name + "\t" + buseo + "\t" +
						gibon + "\t" + sudang + "\t" + total + "\t" + sdf.format(ts));
			}
			System.out.println();
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				if(rs != null) rs.close();
				if(stmt != null) stmt.close();
				if(conn != null) conn.close();
			} catch (Exception e) {
			}
		}
		
		
	}
	
	// db 서버에 연결하는 메서드
	public Connection getConnection() {
		Connection conn = null;
		try {
			conn = DriverManager.getConnection(URL, "bit901", "a1234");
			System.out.println("db 연결 성공!");
		} catch (SQLException e) {
			System.out.println("db 연결 실패: " + e.getMessage());
		}
		
		return conn;
	}
	
	public static void main(String[] args) {
		Ex02_OracleSwan ex = new Ex02_OracleSwan();
		while(true) {
			int n = ex.getMenu();
			switch (n) {
			case 1:
				ex.sawonInsert();
				break;
			case 2:
				ex.sawonAllWrite();
				break;
			case 3:
				ex.sawonSearch();
				break;
			case 4:
				ex.sawonBuseoGroup();
				break;	
			default:
				System.out.println("프로그램 종료!!");
				System.exit(0);
				break;
			}
		}			
	}
}























