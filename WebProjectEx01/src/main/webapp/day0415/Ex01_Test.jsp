<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
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
	/*js, jQuery 영역*/
	$(function(){
		
	});
</script>
</head>
<body>
	<%--
	실제로는 서블릿 객체로 만들어져 서버가 실행
	D:\bitjava0314\javawork\.metadata\.plugins\org.eclipse.wst.server.core\tmp0\work\Catalina\localhost\WebProjectEx01\org\apache\jsp\day0415 
	--%>
	<%=msg%><br>
	<%-- msg2<br> --%>에러남!!!
	
	<%! // 선언문 : 서블릿으로 변환시 멤버변수로 등록
		/*멤버변수*/
		String msg = "Happy day!!";
	%>
	<% 
	    /*지역변수 : 서블릿으로 변환시 지역변수로 등록*/
		/*servlet, 자바영역*/
		String msg2 = "안녕하세요";
	%>
	<!-- 출력은 표현식으로 출력 : 소스보기에서 보임 -->
	<%-- JSP 주석: 소스보기에서 안보임 --%>
	<%=msg%><br>
	<%=msg2%><br>
	
	<%
		String[] str = {"red", "orange", "blue", "pink", "cyan", "manenta"};
	%>
	<table class = "table table-bordered" style="width: 200px;">
		<%
			for(String s : str) {%>
				<tr>
					<th><%=s%></th>
					<td bgcolor="<%=s%>">color</td>
				</tr>
			<%}
		%>
	</table>
	
	
</body>
</html>