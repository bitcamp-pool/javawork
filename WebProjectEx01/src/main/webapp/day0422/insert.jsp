<%@page import="mysql.data.GuestDao"%>
<%@page import="mysql.data.GuestDto"%>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<% 
	// 인코딩 (post)
	request.setCharacterEncoding("UTF-8");

	// 데이터 읽기
	String writer 	= request.getParameter("writer");
	String pass 	= request.getParameter("pass");
	String content 	= request.getParameter("content");
	String avata 	= request.getParameter("avata");
	
	// dto에 넣기
	GuestDto dto = new GuestDto(
			writer,
			pass,
			avata,
			content
			);
	/*
		dto.setWriter(writer);
		dto.setPass(pass);
		dto.setContent(content);
		dto.setAvata(avata);
	*/
	
	// dao선언
	GuestDao dao = new GuestDao();
	
	// insert메서드 호출
	dao.guestInsert(dto);
%>
