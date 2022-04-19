<%@page import="java.text.SimpleDateFormat"%>
<%@page import="mysql.data.StuDto"%>
<%@page import="java.util.List"%>
<%@page import="mysql.data.StuDao"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%
/*
[{"num":7, "name":"강동원",  "photo":"../image/9.jpg",  "hp":"010-7777-8888", "addr":"강원도 삼척",   "writeday":"2022-04-19"}, 
 {"num":1, "name":"김우빈",  "photo":"../image/2.jpg",  "hp":"010-1234-5678", "addr":"서울 강남구",   "writeday":"2022-04-19"}, 
 {"num":2, "name":"박보영",  "photo":"../image/12.jpg", "hp":"010-2222-5678", "addr":"서울 영등포구", "writeday":"2022-04-19"}, 
 {"num":4, "name":"설현",    "photo":"../image/15.jpg", "hp":"010-9999-5678", "addr":"제주도 중문",   "writeday":"2022-04-19"}, 
 {"num":5, "name":"수지",    "photo":"../image/19.jpg", "hp":"010-5656-5678", "addr":"서울 삼성동",   "writeday":"2022-04-19"}, 
 {"num":3, "name":"신민아",  "photo":"../image/17.jpg", "hp":"010-8888-5678", "addr":"제주도 애월읍", "writeday":"2022-04-19"}, 
 {"num":11, "name":"정용관", "photo":"../image/3.jpg",  "hp":"010-1212-8282", "addr":"인천 남동구",   "writeday":"2022-04-19"},]
 마지막 ','지우기
*/
	StuDao dao = new StuDao();
	List<StuDto> list = dao.getAllDatas();
	
	StringBuffer sb = new StringBuffer();
	SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
	
	sb.append("[");
	for(StuDto dto : list){
		sb.append("{\"num\":" 		+ dto.getNum() 		+ ", ");
		sb.append("\"name\":\"" 	+ dto.getName() 	+ "\", ");
		sb.append("\"photo\":\"" 	+ dto.getPhoto() 	+ "\", ");
		sb.append("\"hp\":\"" 		+ dto.getHp() 		+ "\", ");
		sb.append("\"addr\":\"" 	+ dto.getAddr() 	+ "\", ");
		sb.append("\"writeday\":\"" + (sdf.format(dto.getWriteday())) + "\"");
		sb.append("},");
	}
	// 마지막 컴마 제거
	sb.deleteCharAt(sb.length()-1);
	sb.append("]");
%>
<%=sb.toString()%>
