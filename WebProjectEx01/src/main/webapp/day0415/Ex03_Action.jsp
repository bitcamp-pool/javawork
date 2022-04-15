<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
<script src="https://code.jquery.com/jquery-3.5.0.js"></script>   
<link href="https://fonts.googleapis.com/css2?family=Gamja+Flower&family=Jua&family=Lobster&family=Nanum+Pen+Script&display=swap" rel="stylesheet">
<style>
	body * {
		font-size: 2rem;
		font-family: 'Jua';
	}
</style>
</head>
<%
	// 폼 태그 읽기: get 방식일 경우(톰캣8부터 한글 안깨짐)
	String name = request.getParameter("name"); // 리턴타입은 모두 String
	String email = request.getParameter("email");
	String driver = request.getParameter("driver"); 
%>
<body>
	<b>이름 : </b><%=name%><br>
	<b>이메일 : </b><%=email%><br>
	<!--<b>운전면허:</b><%=driver%><br>--> 
	<!--체크여부(on/null), 값을 넣으면 값이 출력-->
	<b>운전면허 : </b><%=driver==null?"없음":"있음"%><br>
</body>
</html>