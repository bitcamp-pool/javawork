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
    <!-- http://localhost:9000/day0428/read1?name=정용관&ipsa=2022-01-01 -->
	<form action="read1" method="get" class="form-inline">
		<table class="table table-bordered" style="width:400px">
			<caption><b>폼 연습 #1</b></caption>
			<tr>
				<th width="100" bgcolor="#ddd">이름</th>
				<td>
					<input type="text" name="name" class="form-control"
						required="required" autofocus="autofocus">
				</td>
			</tr>
			<tr>
				<th width="100" bgcolor="#ddd">입사일</th>
				<td>
					<input type="date" name="ipsa" class="form-control"
						   value="2022-01-01">
				</td>
			</tr>
			<tr>
				<td colspan="2" align="center">
					<button type="submit" class="btn btn-info">서버 전송</button>
				</td>
			</tr>
		</table>
	</form>
</body>

</html>























