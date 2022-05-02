<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
<script src="https://code.jquery.com/jquery-3.5.0.js"></script>   
<link href="https://fonts.googleapis.com/css2?family=Gamja+Flower&family=Jua&family=Lobster&family=Nanum+Pen+Script&display=swap" rel="stylesheet">
<style type="text/css">
   body{
      font-size: 2rem;
      font-family: 'Jua';
   }
</style>
</head>
<body>
   <h1>${message}</h1>
   <h2>리소스의 이미지 출력</h2>
   <img alt="" src="s1.JPG"><img alt="" src="s2.JPG">
   <br><br>
   <button type="button" class="btn btn-default" 
   		   style="width:130px;" onclick="location.href='form'">자동차 정보 추가
   </button>
   <br>
</body>
</html>






