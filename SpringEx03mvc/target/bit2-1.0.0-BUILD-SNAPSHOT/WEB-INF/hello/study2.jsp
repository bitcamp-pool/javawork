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
	body {
		font-family: 'Jua';
		font-size: 2em;
	}
</style>
<script type="text/javascript">
  window.onload=function(){
    
  }
</script>
</head>

<body>
<h1>go 1 페이지로부터 포워드된 jap 파일</h1>
	이름 : ${name }<br>
	주소 : ${addr }<br>
<hr>

<h3>resources 폴더의 c6.png 이미지 출력</h3>
<img alt="" src="res/c6.png" style="width:100px;">

<h3>avata 폴더의 s6.JPG 이미지 출력</h3>
<img alt="" src="avata/s6.JPG" style="width:100px;">

<h3>image 폴더의 12.jpg 이미지 출력</h3>
<img alt="" src="image/12.jpg" style="width:100px;">

</body>
</html>