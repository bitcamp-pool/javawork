<?xml version="1.0" encoding="UTF-8"?>
<% 
/* 
xml 파일을 브라우저에 전달하기 위한 설정
첫 줄에 아무것도 없어야 한다

외부 클래스 import */
%>
<%@page import="java.text.SimpleDateFormat"%>
<%@page import="mysql.data.StuDto"%>
<%@page import="java.util.List"%>
<%@page import="mysql.data.StuDao"%>
<%//contentType의 text/html을 /xml로 수정 %>
<%@ page language="java" contentType="text/xml; charset=UTF-8" pageEncoding="UTF-8"%>

<%
	// Ctrl + Space 자동 import
	StuDao dao = new StuDao();
	List<StuDto> list = dao.getAllDatas();
	
%>
<list>
	<%
	SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm");
	for (StuDto dto : list)
	{%>
		<stu>
			<num><%=dto.getNum()%></num>
			<name><%=dto.getName()%></name>
			<photo><%=dto.getPhoto() %></photo>
			<hp><%=dto.getHp()%></hp>
			<addr><%=dto.getAddr()%></addr>
			<writeday><%=sdf.format(dto.getWriteday())%></writeday>
		</stu>
	<%}
	%>
</list>
