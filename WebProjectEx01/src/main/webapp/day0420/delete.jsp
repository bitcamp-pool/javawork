<%@page import="mysql.data.ShopDto"%>
<%@page import="mysql.data.ShopDao"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>

<%
	
	// 요청 페이지(delete.jsp)로부터 num 읽기
	String num = request.getParameter("num");

	// dao 선언
	ShopDao dao = new ShopDao();
	
	// dao로부터 num에 해당하는 dto 얻기
	dao.shopDelete(num);
	
%>
