<%@page import="com.google.gson.JsonObject"%>
<%@page import="mysql.data.ShopDto"%>
<%@page import="mysql.data.ShopDao"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>

<%
	/*JSON : html 주석 허용안함(오류발생)*/
	
	// 디테일 페이지로부터 num 읽기
	String num = request.getParameter("num");

	// dao 선언
	ShopDao dao = new ShopDao();
	
	// dao로부터 num에 해당하는 dto 얻기
	ShopDto dto = dao.getSangpum(num);
	
	// json으로 변환
	JsonObject obj = new JsonObject();
	
	obj.addProperty("num", 		dto.getNum()); 
	obj.addProperty("sangpum",	dto.getSangpum());
	obj.addProperty("color", 	dto.getColor());
	obj.addProperty("price", 	dto.getPrice());
	obj.addProperty("photo", 	dto.getPhoto());
	obj.addProperty("cnt", 		dto.getCnt());
	obj.addProperty("ipgoday", 	dto.getIpgoday());
%>
<%=obj.toString()  %>