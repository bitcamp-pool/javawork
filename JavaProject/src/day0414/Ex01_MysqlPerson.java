package day0414;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.Scanner;

public class Ex01_MysqlPerson {

	static final String DRIVER = "com.mysql.cj.jdbc.Driver";
//	static final String URL = "jdbc:mysql://localhost:3306/bit901"; //5버전
    static final String URL = "jdbc:mysql://localhost:3306/bit901?serverTimezone=Asia/Seoul"; //8버전 serverTimezone="UTC"
	Scanner sc = new Scanner(System.in);
	
	public Ex01_MysqlPerson() {
		try {
			Class.forName(DRIVER);
			System.out.println("mysql 드라이버 성공");
		} catch (ClassNotFoundException e) {
			System.out.println("mysql 드라이버 실패: " + e.getMessage());
		}
	}
	
	// db 서버에 연결하는 메서드
	public Connection getConnection() {
		Connection conn = null;
		try {
			conn = DriverManager.getConnection(URL, "bit901", "a1234");
//			conn = DriverManager.getConnection(URL, "root", "1234");
			System.out.println("db 연결 성공!");
		} catch (SQLException e) {
			System.out.println("db 연결 실패: " + e.getMessage());
		}
		return conn;
	}
	
	public int getMenu() {
		System.out.println("-------------------------------------------------");
		System.out.println("** 메뉴선택 **");
		System.out.println("1.추가  2.전체출력  3.삭제  4.분석  5.수정  6.종료");
	    int n = Integer.parseInt(sc.nextLine());
	    return n;
	}
	
	public void personInsert() {
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = "";
		
		// 필요한 데이터 입력
		System.out.print("이름 입력: ");
		String name = sc.nextLine();
		
		System.out.print("혈액형 입력: ");
		String blood = sc.nextLine();
		
		System.out.print("나이 입력: ");
		int age = Integer.parseInt(sc.nextLine());
		
		// db 연결
		conn = this.getConnection();
		sql = "insert into person (name, blood, age, writeday) "
				+ "values (?,?,?,now())";
		
		try {
			pstmt = conn.prepareStatement(sql);
			
			// 반드시 ?표 갯수만큼 타입별로 바인딩 처리:1번부터 시작~
			pstmt.setString(1, name);
			pstmt.setString(2, blood);
			pstmt.setInt(3, age);
			
			// 실행
			pstmt.execute();
			
			System.out.println("DB에 데이터가 추가되었어요!!");
			
		} catch (SQLException e) {
			System.out.println("insert 오류: " + e.getMessage());
		} finally {
			try {
				if(pstmt != null) pstmt.close();
				if(conn != null) conn.close();
			} catch (Exception e2) {
				
			}
		}
	}
	
	public void personDelete() {
		// 이름을 입력 후 해당 데이터 삭제
		// 삭제 후 "삭제되었습니다" 메시지 출력
		// 이름이 없으면 "OOO님은 명단에 없습니다." 출력
		String name = "";
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = "delete from person where name = ?";
		
		System.out.println("삭제할 이름 입력");
		name = sc.nextLine();
		// db 연결
		conn = this.getConnection();		
		try {
			pstmt = conn.prepareStatement(sql);
			// ? 에 바인딩
			pstmt.setString(1, name);
			// 실행
			int n = pstmt.executeUpdate(); // 성공한 레코드의 개수 반환
//			pstmt.execute();
			if(n == 0)
				System.out.println(name + " 님은 명단에 없습니다");
			else
				System.out.println("총 " + n + "명의 " + name + "님이 삭제되었습니다");
			
		} catch (SQLException e) {
		} finally {
			try {
				if(pstmt != null) pstmt.close();
				if(conn != null) conn.close();
			} catch (Exception e) {
				
			}
		}
		
	}
	
	public void personBloodGroup() {
		// 혈액형별 인원수와 평균 나이 출력(group by)
		/* 
		 * 혈액형	인원수	평균나이1
		 * A형		2		32(정수로)
		 * B형		3		40
		 */
		
		String sql = 	"select upper(blood) blood, count(blood) count, round(avg(age), 0) age "
					+ 	"from person p "
					+ 	"group by blood;";
		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		
		conn = this.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			// 데이터 출력
			System.out.println("\t** 혈액형별 분석표 **");
			System.out.println();
			System.out.println("혈액형\t인원수\t평균나이");
			while(rs.next()) {
				String blood = rs.getString("blood");
				int count = rs.getInt("count");
				int age = rs.getInt("age");
				
				System.out.println(blood + "형\t" + count + "명\t" +  age + "세");
			}
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			try {
				if(rs != null) rs.close();
				if(pstmt != null) pstmt.close();
				if(conn != null) conn.close();
			} catch (Exception e) {
				
			}
		}
	}
	
	public void personUpdate() {
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = "";
		int num, age;
		String blood;
		
		System.out.print("수정할 num 값 입력: ");
		num = Integer.parseInt(sc.nextLine());
		System.out.print("수정할 blood 값 입력: ");
		blood = sc.nextLine();
		System.out.print("수정할 나이 입력: ");
		age = Integer.parseInt(sc.nextLine());
		
		sql = "update person set blood = ?, age = ? where num = ?";
		conn = this.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			// 바인딩
			pstmt.setString(1, blood);
			pstmt.setInt(2, age);
			pstmt.setInt(3, num);
			// 실행
			int n = pstmt.executeUpdate();
			if(n == 0)
				System.out.println("해당 번호가 존재하지 않습니다");
			else
				System.out.println("수정되었습니다");
			
		} catch (SQLException e) {
			e.printStackTrace();
		}  finally {
			try {
				if(pstmt != null) pstmt.close();
				if(conn != null) conn.close();
			} catch (Exception e) {
				
			}
		}
	}
	
	public void personAllWrite() {
		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = "select * from person order by name";
		
		// db 연결
		conn = this.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			
			// 데이터 출력
			SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm");
			System.out.println("\t** Person DB 목록 **");
			System.out.println();
			System.out.println("번호\t이름\t혈액형\t나이\t작성일");
			
			while(rs.next()) {
				int num = rs.getInt("num");
				String name = rs.getString("name");
				String blood = rs.getString("blood").toUpperCase();//대문자로
				int age = rs.getInt("age");
				Timestamp ts = rs.getTimestamp("writeday");
				
				System.out.println(num + "\t" + name + "\t" + 
				       blood + "\t" + age + "\t" + sdf.format(ts));
			}
			
		} catch (Exception e) {
			
		} finally {
			try {
				if(rs != null) rs.close();
				if(pstmt != null) pstmt.close();
				if(conn != null) conn.close();
			} catch (Exception e) {
			}
		}
	}
	
	public static void main(String[] args) {
		Ex01_MysqlPerson ex = new Ex01_MysqlPerson();
		
		while(true) {
			int n = ex.getMenu();
			switch (n) {
			case 1:
				ex.personInsert();
				break;
			case 2:
				ex.personAllWrite();
				break;
			case 3:
				ex.personDelete();
				break;
			case 4:
				ex.personBloodGroup();
				break;
			case 5:
				ex.personUpdate();
				break;	
			default:
				System.out.println("프로그램 종료!!");
				System.exit(0);
				break;
			}
		}			
	}
}
