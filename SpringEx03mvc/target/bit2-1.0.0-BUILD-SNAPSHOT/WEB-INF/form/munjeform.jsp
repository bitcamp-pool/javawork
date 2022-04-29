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

	<form action="result" method="post" class="form-inline">
		<table class="table table-bordered" style="width:400px">
			<caption><b>점수입력</b></caption>
			<tr>
				<th width="100" bgcolor="#ddd">이름</th>
				<td>
					<input type="text" name="name" class="form-control"
						required="required" autofocus="autofocus">
				</td>
			</tr>
			<tr>
				<th width="100" bgcolor="#ddd">사진</th>
				<td>
					<select name="photo" class="form-control">
						<option value="../image/1.jpg">사진1</option>	   
						<option value="../image/3.jpg">사진3</option>	   
						<option value="../image/6.jpg">사진6</option>	   
						<option value="../image/9.jpg">사진9</option>	   
					</select>	   
				</td>
			</tr>			
			<tr>
				<th width="100" bgcolor="#ddd">자바</th>
				<td>
					<input type="text" name="java" class="form-control"
						required="required">
				</td>
			</tr>
			<tr>
				<th width="100" bgcolor="#ddd">스프링</th>
				<td>
					<input type="text" name="spring" class="form-control"
						   required="required">
				</td>
			</tr>
			<tr>
				<td colspan="2" align="center">
					<button type="submit" class="btn btn-info">결과</button>
				</td>
			</tr>
		</table>
	</form>
	
</body>

</html>























