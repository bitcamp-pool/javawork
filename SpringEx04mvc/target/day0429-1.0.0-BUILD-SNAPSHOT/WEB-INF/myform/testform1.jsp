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

	<form action="read1" method="post" class="form-inline">
		<table class="table table-bordered" style="width:400px">
			<caption><b>폼 연습 #1(Map으로 읽기)</b></caption>
			<tr>
				<th width="100" bgcolor="#ddd">상품명</th>
				<td>
					<input type="text" name="sang" class="form-control"
						required="required" autofocus="autofocus">
				</td>
			</tr>
			<tr>
				<th width="100" bgcolor="#ddd">수량</th>
				<td>
					<input type="text" name="su" class="form-control"
						required="required">
				</td>
			</tr>
			<tr>
				<th width="100" bgcolor="#ddd">가격</th>
				<td>
					<input type="text" name="price" class="form-control"
						   required="required">
				</td>
			</tr>
			<tr>
				<th width="100" bgcolor="#ddd">사진</th>
				<td>
					<select name="photo" class="form-control">
						<option value="K-034">사진1</option>	   
						<option value="K-035">사진2</option>	   
						<option value="K-036">사진3</option>	   
						<option value="K-037">사진4</option>	   
					</select>	   
				</td>
			</tr>
			<tr>
				<th width="100" bgcolor="#ddd">입고일</th>
				<td>
					<input type="date" name="ipgoday" class="form-control"
						   value="2022-01-01">
				</td>
			</tr>	
			<tr>
				<th width="100" bgcolor="#ddd">색상</th>
				<td>
					<input type="color" name="color" class="form-control"
						   value="#ffffcc" style="width:150px">
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























