package mysql.data;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Vector;

public class ShopDao {
	DbConnect db = new DbConnect();
	
	// 데이터 추가
	public void shopInsert(ShopDto dto) {
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = "insert into shop (" +
				"sangpum, photo, price, color, cnt, ipgoday) values (?,?,?,?,?,?)";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			
			// 바인딩
			pstmt.setString(1, dto.getSangpum());
			pstmt.setString(2, dto.getPhoto());
			pstmt.setInt(3, dto.getPrice());
			pstmt.setString(4, dto.getColor());
			pstmt.setInt(5, dto.getCnt());
			pstmt.setString(6, dto.getIpgoday());
			
			// 실행
			pstmt.execute();
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			db.dbClose(pstmt, conn);
		}
	}
	
	// 데이터 삭제
	public void shopDelete(String num) {
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = "delete from shop where num=?";
		
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
	
	// 데이터 수정
	public void shopUpdate(ShopDto dto) {
		Connection conn = null;
		PreparedStatement pstmt = null;
		String sql = "update shop set sangpum=?, color=?, price=?, cnt=?, ipgoday=?, photo=? where num=?";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			// 바인딩
			pstmt.setString(1, dto.getSangpum());
			pstmt.setString(2, dto.getColor());
			pstmt.setInt(3, dto.getPrice());
			pstmt.setInt(4, dto.getCnt());
			pstmt.setString(5, dto.getIpgoday());
			pstmt.setString(6, dto.getPhoto());
			pstmt.setString(7, dto.getNum());
			// 실행
			pstmt.execute();
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			db.dbClose(pstmt, conn);
		}
	}
	
	
	// 데이터 조회
	public List<ShopDto> getSangpumList(){
		List<ShopDto> list = new Vector<ShopDto>();
		
		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = "select * from shop order by num desc";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			rs=pstmt.executeQuery();
			while(rs.next()) {
				ShopDto dto = new ShopDto();
				
				dto.setNum(rs.getString("num"));
				dto.setSangpum(rs.getString("sangpum"));
				dto.setColor(rs.getString("color"));
				dto.setPhoto(rs.getString("photo"));
				dto.setPrice(rs.getInt("price"));
				dto.setCnt(rs.getInt("cnt"));
				dto.setIpgoday(rs.getString("ipgoday"));
				
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
	
	// 상품명(num)에 해당하는 dto 반환
	public ShopDto getSangpum(String num) {
		ShopDto dto = new ShopDto();
		
		Connection conn = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		String sql = "select * from shop where num=?";
		
		conn = db.getConnection();
		try {
			pstmt = conn.prepareStatement(sql);
			// 바인딩 및 실행
			pstmt.setString(1, num);
			rs=pstmt.executeQuery();
			// 여러개 while(), 1개 if()
			if (rs.next()) {
				dto.setNum(rs.getString("num"));
				dto.setSangpum(rs.getString("sangpum"));
				dto.setColor(rs.getString("color"));
				dto.setPhoto(rs.getString("photo"));
				dto.setPrice(rs.getInt("price"));
				dto.setCnt(rs.getInt("cnt"));
				dto.setIpgoday(rs.getString("ipgoday"));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			db.dbClose(rs, pstmt, conn);
		}
		
		return dto;
	}
}























