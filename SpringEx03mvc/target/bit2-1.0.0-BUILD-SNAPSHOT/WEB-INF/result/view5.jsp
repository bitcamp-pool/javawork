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

	<h1>
		<!-- 보이는 대로 출력하기 위해 pre 태그 사용 -->
		<pre>
			이름: ${personDto.name}<br>
			사진: <img style="width:100px;" src="${personDto.photo}"/><br>
			자바점수   : ${personDto.java} 점<br>
			스프링점수 : ${personDto.spring} 점<br>
			총점        : ${personDto.java + personDto.spring} 점<br>
			평균        : <fmt:formatNumber value="${(personDto.java + personDto.spring)/2}" pattern="##.0" />
		</pre>
	</h1>

</body>
</html>