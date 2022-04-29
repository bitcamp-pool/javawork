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
		font-size:2rem;
		font-family: 'Jua';
	}
	div.color{
		width: 100px;
		height: 100px;
		border: 1px solid black;
		border-radius: 100px;
	}
</style>
<script type="text/javascript">
  window.onload=function(){
    
  }
</script>
</head>

<body>
	<h2>
		상품명 : ${sang}<br>
		수  량 : ${su}개<br>
		가  격 : <fmt:formatNumber value="${price}" type="currency"/><br>
		색  상 : <div style="background-color:${color}" class="color"></div>
		입고일 : ${ipgoday}<br>
		사  진 : <img src ="../res/image/${photo}.png" width="200"> 
	</h2>
</body>
</html>














