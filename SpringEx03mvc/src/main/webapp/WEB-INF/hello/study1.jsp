<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@taglib prefix="c"    uri="http://java.sun.com/jsp/jstl/core"%>
<%@taglib prefix="fmt"  uri="http://java.sun.com/jsp/jstl/fmt"%>
    
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
<script src="https://code.jquery.com/jquery-3.5.0.js"></script>   
<link href="https://fonts.googleapis.com/css2?family=Gamja+Flower&family=Jua&family=Lobster&family=Nanum+Pen+Script&display=swap" rel="stylesheet">
<style type="text/css">
	/*css 영역*/
</style>
<script type="text/javascript">
  window.onload=function(){
    
  }
</script>
</head>

<body>
	<h1 style="font-family: 'Jua'">${message }</h1>
	<h2 style="font-family: 'Lobster'">
		<fmt:formatDate value="${today }" pattern="yyyy-MM-dd a hh:mm EEEE"/>
	</h2>
	
	<!-- 이미지는 url depth에 따라 경로가 서로 다르다. -->
	<h1><a href="go1">go1 페이지로 이동</a></h1>
	<h1><a href="go2/busan/sea">go2/busan/sea 페이지로 이동</a></h1>
	<h1><a href="go3">go3 페이지로 이동</a></h1>
	<h1><a href="go3/jeju">go3/jeju 페이지로 이동</a></h1>
	<h1><a href="go3/seoul">go3/seoul 페이지로 이동</a></h1>
	
	<h3>res 폴더의 이미지 접근</h3>
	<img alt="" src="res/c1.png" width="130">
	
	<h3>avata 폴더의 이미지 접근</h3>
	<img alt="" src="avata/s10.JPG">
	
	<h3>image 폴더의 이미지 접근</h3>
	<img alt="" src="image/13.jpg" width="150">
	<br>
	
	<h1>
	<a href="go1">go 1 페이지로 이동</a>
	</h1>
	
	<h1>
	<a href="go2/busan/sea">go2/busan/sea 페이지로 이동</a>
	</h1>
		
</body>
</html>




































