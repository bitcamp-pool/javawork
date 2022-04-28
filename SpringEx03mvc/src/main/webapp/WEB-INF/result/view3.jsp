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
			상품명 : ${shopDto.sang}
			수  량 : ${shopDto.su} 개
			가  격 : <fmt:formatNumber value="${shopDto.price}" type="currency"/>
			사  진 : <img src="${shopDto.photo}"/>
		</pre>
	</h1>

</body>
</html>