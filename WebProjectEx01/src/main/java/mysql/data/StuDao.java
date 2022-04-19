package mysql.data;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/* DAO(Data Access Object)
 * 
 */
public class StuDao {
	DbConnect db = new DbConnect();
	
	// 출력
	public List<StuDto> getAllDatas(){
		List<StuDto> list = new ArrayList<StuDto>();
		
		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = "select * from stu order by name";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			rs = pstmt.executeQuery();
			while(rs.next()) {
				
				// db의 테이터를 레코드 단위로 dto에 넣는다
				StuDto dto = new StuDto();
				
				dto.setNum(rs.getString("num"));
				dto.setPhoto(rs.getString("photo"));
				dto.setName(rs.getString("name"));
				dto.setHp(rs.getString("hp"));
				dto.setAddr(rs.getString("addr"));
				dto.setWriteday(rs.getTimestamp("writeday"));
				
				// list에 추가
				list.add(dto);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			db.dbClose(rs, pstmt, conn);
		}
		
		return list;
	}
	
	// Insert method
	public void insertStudent(StuDto dto) {
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = "insert into stu (name, hp, addr, photo, writeday) values (?,?,?,?,now())";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			
			// 바인딩(순서에 맞게)
			pstmt.setString(1, dto.getName());
			pstmt.setString(2, dto.getHp());
			pstmt.setString(3, dto.getAddr());
			pstmt.setString(4, dto.getPhoto());
			
			// 실행
			pstmt.execute();
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			db.dbClose(pstmt, conn);
		}
	}
	
	// 삭제 메서드
	public void deleteStudent(String num) {
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = "delete from stu where num=?";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			// 바인딩
			pstmt.setString(1, num);
			// 실행
			pstmt.execute();
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			db.dbClose(pstmt, conn);
		}
	}
}


















