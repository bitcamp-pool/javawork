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
	body * {
		font-size: 23px;
		font-family: 'Jua';
	}
</style>
<script type="text/javascript">
  window.onload=function(){
    
  }
</script>
</head>

<body>

	<b>오늘날짜 : <fmt:formatDate value ="${today }" pattern="yyyy-MM-dd"/></b>
	
	<h2>list 컬렉션의 TestDto 출력하기</h2>
	<table class="table table-bordered" style="width: 400px;">
		<tr>
			<th>번호</th><th>이름</th><th>핸드폰</th><th>주소</th>
		</tr>
		<c:forEach var="e" items="${list }" varStatus="i">
			<!-- 실제로는 getter 메서드가 호출 : e.getName() -->
			<tr>
				<td>${i.count}</td>
				<td>${e.name}</td>
				<td>${e.hp}</td>
				<td>${e.addr}</td>
			</tr>
		</c:forEach>
	</table>
	<hr>
	
	<h2>forTokens 연습</h2>
	<c:set var="str" value="red, green, blue, orange, pink, magenta"/>
	${str}<br>
	<c:forTokens var= "s" items="${str}" delims="," varStatus="i">
		<b style='color:${s}'>${i.count} : ${s}</b><br>
	</c:forTokens>
	
</body>
</html>








































