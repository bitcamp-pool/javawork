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
	table * {
		font-family: 'Jua';
		font-size: 1.3rem;
	}
	table thead tr {
	 	background-color: orange;
	 	color: white;
	}
	table tr {
		text-align: center;
	}
</style>
</head>
<body>
	<table class="table table-bordered" style="width: 1000px;">
		<thead>
			<tr>
			<%
				for(int dan=2; dan<=9; dan++){%>
					<td>[<%=dan%>단]</td>
			  <%}
			%>
			</tr>
		</thead>
		<tbody>
			<%
			for(int i=1; i<=9; i++) 
			{%>
				<tr>
				<% 
				for(int dan=2; dan<=9; dan++)
				{%>
					<td><%=dan%>x<%=i%>=<%=dan * i%></td>
				<%}
				%>
				</tr>
			<%} 
			%>
		</tbody>
	</table>
</body>
</html>