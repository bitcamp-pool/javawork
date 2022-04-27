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
		font-size: 2rem;
		font-family: 'Jua';
	}
</style>
<script type="text/javascript">
  window.onload=function(){
    
  }
</script>
</head>

<body>
	<c:forEach var="n" begin="1" end="10">
		${n}&nbsp;
	</c:forEach>
	<br>
	
	<c:forEach var="n" begin="1" end="10" step="2">
		${n}&nbsp;
	</c:forEach>
	<br>
	
	<table class="table table-bordered" style="width:300px">
		<tr bgcolor="#ddd">
			<th>index</th><th>count</th><th>value</th>
		</tr>
		
		<c:forEach var="s" items="${flowers}" varStatus="i">
			<tr>
				<td>${i.index}</td>
				<td>${i.count}</td>
				<td bgcolor="${s}">${s}</td>
			</tr>
		</c:forEach>
	</table>
	
	<h2>인덱스 2~4 까지만 출력하기</h2>
	<table class="table table-bordered" style="width:300px">
		<tr bgcolor="#ddd">
			<th>index</th><th>count</th><th>value</th>
		</tr>
		
		<c:forEach var="s" items="${flowers}" begin="2" end="4" varStatus="i">
			<tr>
				<td>${i.index}</td>
				<td>${i.count}</td>
				<td bgcolor="${s}">${s}</td>
			</tr>
		</c:forEach>
	</table>	
	<h2>인덱스 1~3 까지만 출력하기</h2>
	<table class="table table-bordered" style="width:300px">
		<tr bgcolor="#ddd">
			<th>index</th><th>count</th><th>value</th>
		</tr>
		
		<c:forEach var="s" items="${flowers}" begin="1" end="3" varStatus="i">
			<tr>
				<td>${i.index}</td>
				<td>${i.count}</td>
				<td bgcolor="${s}">${s}</td>
			</tr>
		</c:forEach>
	</table>	
	
	
	
	
</body>
</html>
































