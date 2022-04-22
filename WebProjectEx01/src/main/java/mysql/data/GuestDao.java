package mysql.data;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Vector;

public class GuestDao {
	DbConnect db = new DbConnect();
	
	// INSERT(데이터 추가)
	public void guestInsert(GuestDto dto) {
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = 
				"insert into guest (" +
				"writer, pass, avata, content, writeday) values (?,?,?,?,now())";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			
			// 바인딩
			pstmt.setString(1, dto.getWriter());
			pstmt.setString(2, dto.getPass());
			pstmt.setString(3, dto.getAvata());
			pstmt.setString(4, dto.getContent());
		
			// 실행
			pstmt.execute();
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			db.dbClose(pstmt, conn);
		}
	}
	
	// UPDATE(데이터 수정)
	public void guestUpdate(GuestDto dto) {
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = 
				"update guest set " +
				"writer=?, avata=?, content=? where num=?";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			
			// 바인딩
			pstmt.setString(1, dto.getWriter());
			pstmt.setString(2, dto.getAvata());
			pstmt.setString(3, dto.getContent());
			pstmt.setString(4, dto.getNum());
		
			// 실행
			pstmt.execute();
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			db.dbClose(pstmt, conn);
		}
	}
	
	// DELETE(삭제)
	public void geustDelete(String num) {
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = "delete from guest where num=?";
		
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
	
	// PASSCHECK(비번이 맞으면 TRUE)
	public boolean isEqualPass(String num, String pass) {

		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = "select * from guest where num=? and pass=?";
		
		boolean result = false;
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			// 바인딩 및 실행
			pstmt.setString(1, num);
			pstmt.setString(2, pass);
			rs=pstmt.executeQuery();
			// 비번이 맞는 경우
			if (rs.next()) { 
				result = true;
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			db.dbClose(rs, pstmt, conn);
		}
		
		return result;
	}
	
	// SELECT(전체조회)
	public List<GuestDto> getAllGuest(){
		List<GuestDto> list = new Vector<GuestDto>();
		
		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = "select * from guest order by num desc";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				GuestDto dto = new GuestDto();
				
				dto.setNum(rs.getString("num"));
				dto.setWriteday(rs.getTimestamp("writeday"));
				dto.setWriter(rs.getString("writer"));
				dto.setAvata(rs.getString("avata"));
				dto.setContent(rs.getString("content"));
				
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
	
	// SELECT(상세조회 : num에 대한 데이터 반환)
	public GuestDto getGuest(String num) {
		GuestDto dto = new GuestDto();
		
		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = "select * from guest where num=?";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			// 바인딩 및 실행
			pstmt.setString(1, num);
			rs=pstmt.executeQuery();
			// 여러개 while(), 1개 if()
			if (rs.next()) {
				dto.setNum(rs.getString("num"));
				dto.setWriteday(rs.getTimestamp("writeday"));
				dto.setWriter(rs.getString("writer"));
				dto.setAvata(rs.getString("avata"));
				dto.setContent(rs.getString("content"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			db.dbClose(rs, pstmt, conn);
		}
		
		return dto;
	}
}
