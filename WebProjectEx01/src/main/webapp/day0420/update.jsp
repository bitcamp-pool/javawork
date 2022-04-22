<%@page import="mysql.data.ShopDao"%>
<%@page import="mysql.data.ShopDto"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>

<%
	// 한글 인코딩
	request.setCharacterEncoding("UTF-8");

	// 데이터 읽기
	String num 		= request.getParameter("unum");
	String sangpum 	= request.getParameter("usangpum");
	String color 	= request.getParameter("ucolor");
	String ipgoday 	= request.getParameter("uipgoday");
	String photo 	= request.getParameter("uphoto");
	int cnt 		= Integer.parseInt(request.getParameter("ucnt"));
	int price 		= Integer.parseInt(request.getParameter("uprice"));
	
	// dto 에 넣기
	ShopDto dto = new ShopDto();
	
	dto.setNum(num);
	dto.setSangpum(sangpum);
	dto.setColor(color);
	dto.setPhoto(photo);
	dto.setPrice(price);
	dto.setCnt(cnt);
	dto.setIpgoday(ipgoday);
	
	// dao 선언
	ShopDao dao = new ShopDao();

	// update 메서드 호출
	dao.shopUpdate(dto);
	
%>