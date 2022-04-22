<%@page import="java.text.SimpleDateFormat"%>
<%@page import="com.google.gson.JsonObject"%>
<%@page import="com.google.gson.JsonArray"%>
<%@page import="mysql.data.GuestDto"%>
<%@page import="java.util.List"%>
<%@page import="mysql.data.GuestDao"%>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<% 
	// json 배열타입으로 나오도록 코딩
	// 날짜는 년월일시분까지만 나오게(SimpleDataFormat)
	
	// dao에서 목록 가져오기
	GuestDao dao = new GuestDao();
	List<GuestDto> list = dao.getAllGuest();
	SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm");
	
	// json 형태로 변환
	JsonArray arr = new JsonArray();
	
	for(GuestDto dto : list){
		JsonObject obj = new JsonObject();
		
		obj.addProperty("num", dto.getNum());
		obj.addProperty("writer", dto.getWriter());
		obj.addProperty("avata", dto.getAvata());
		obj.addProperty("content", dto.getContent());
		obj.addProperty("writeday", sdf.format(dto.getWriteday()));
		
		// arr에 추가
		arr.add(obj);
	}
%>
<%=arr.toString()%>