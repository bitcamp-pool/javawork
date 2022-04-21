<%@page import="mysql.data.ShopDao"%>
<%@page import="mysql.data.ShopDto"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>

<% 
	// 데이터 읽기
	String sangpum 	= request.getParameter("sangpum");
	String color 	= request.getParameter("color");
	String ipgoday 	= request.getParameter("ipgoday");
	String photo 	= request.getParameter("photo");
	int cnt 		= Integer.parseInt(request.getParameter("cnt"));
	int price;
	
	try {
		price = Integer.parseInt(request.getParameter("price"));
	} catch(NumberFormatException e){
		// 문자가 섞여 있을 경우 발생
		System.out.println("입력값 오류");
		price = 0;
	}
	
	// dto 에 넣기
	ShopDto dto = new ShopDto();
	
	dto.setSangpum(sangpum);
	dto.setColor(color);
	dto.setPhoto(photo);
	dto.setPrice(price);
	dto.setCnt(cnt);
	dto.setIpgoday(ipgoday);
	
	// dao 선언
	ShopDao dao = new ShopDao();

	// insert 메서드 호출
	dao.shopInsert(dto);
%>
