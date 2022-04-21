<%@page import="com.google.gson.JsonArray"%>
<%@page import="com.google.gson.GsonBuilder"%>
<%@page import="com.google.gson.JsonObject"%>
<%@page import="org.json.simple.JSONObject"%>
<%@page import="org.json.simple.JSONArray"%>
<%@page import="mysql.data.ShopDto"%>
<%@page import="java.util.List"%>
<%@page import="mysql.data.ShopDao"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>

<%
/*
라이브러리 설치
https://code.google.com/archive/p/json-simple/downloads
http://mvnrepository.com
Gson 라이브러리( Json 생성, 변환 )
: Gson은 Java에서 Json을 파싱하고, 생성하기 위해 사용되는 구글에서 개발한 오픈소스
  Java Object를 Json 문자열로 변환할 수 있고, Json 문자열을 Java Object로 변환
https://search.maven.org/artifact/com.google.code.gson/gson/2.8.7/jar
*/

// dao 에서 list 가져오기
ShopDao dao = new ShopDao();
List<ShopDto> list = dao.getSangpumList();

// json 형태로 변환
JsonArray arr = new JsonArray();
for(ShopDto dto : list){
	JsonObject obj = new JsonObject();
	
	obj.addProperty("sangpum",	dto.getSangpum());
	obj.addProperty("photo", 	dto.getPhoto());
	obj.addProperty("color", 	dto.getColor());
	obj.addProperty("price", 	dto.getPrice());
	obj.addProperty("cnt", 		dto.getCnt());
	obj.addProperty("ipgoday", 	dto.getIpgoday());
	obj.addProperty("num", 		dto.getNum()); 
	
	arr.add(obj);
}

/*
	JSONArray arr = new JSONArray();
	
	for(ShopDto dto : list){
		
 		JSONObject ob = new JSONObject();
		
		ob.put("sangpum", dto.getSangpum());
		ob.put("photo", dto.getPhoto());
		ob.put("color", dto.getColor());
		ob.put("price", dto.getPrice());
		ob.put("cnt", dto.getCnt());
		ob.put("ipgoday", dto.getIpgoday());
		ob.put("num", dto.getNum()); 
		
		// arr에 추가
		arr.add(ob);
	}
*/
%>
<%=arr.toString()%>    
