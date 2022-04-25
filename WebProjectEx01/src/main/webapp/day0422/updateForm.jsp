<%@page import="mysql.data.GuestDto"%>
<%@page import="mysql.data.GuestDao"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<meta name="viewport" content="width=device-width;initial-scale=1.0">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
<script src="https://code.jquery.com/jquery-3.5.0.js"></script>   
<link href="https://fonts.googleapis.com/css2?family=Gamja+Flower&family=Jua&family=Lobster&family=Nanum+Pen+Script&display=swap" rel="stylesheet">
<style>
	img.imgphoto{
		width: 55px;
		height: 55px;
		margin-right: 3px;
		cursor: pointer;
	}
	
	.select{
		border: 2px solid black;
		box-shadow: 3px 3px 3px gray;
	}
	
	.table{
		width:500px;
		border: 1px solid black;
		font-family: 'Jua';
		font-size: 20px;
	}
</style>
<script type="text/javascript">
	$(function(){
		$(".btnupdate").click(function() {
			var fdata = $("#frm").serialize();
			$.ajax({
				type:"post",
				dataType:"html",
				data:fdata,
				url:"update.jsp",
				success:function(){
					// 수정 성공시 메인페이지로 이동
					location.href = "GuestMain.jsp";
				}
			});
		});
	});
</script>
</head>

<%
	String num=request.getParameter("num");

	//num  에 해당하는 dto 받기
	GuestDao dao=new GuestDao();
	GuestDto dto=dao.getGuest(num);
%>
<body>
<form id="frm" class="form-inline">
		<caption><b>수정폼</b></caption>
 		<input type="hidden" id="num" name="num" value="<%=num%>">
	  	<table class="table">
	  		<tr>
		  		<td width="350">
		  		  작성자 : <input type="text" id="writer" name="writer" class="form-control"
		  		            style="width: 100px;" value="<%=dto.getWriter()%>">		  		          
		  		</td>
		  		<td rowspan="3" style="cursor: pointer;background-color: orange;"
		  		 align="center" valign="middle" class="btnupdate">
		  		수정
		  		</td>
	  		</tr>
	  		
	  		<tr>
	  			<td>
	  				<textarea id="content" name="content" style="width: 100%;height: 80px;"><%=dto.getContent()%></textarea>
	  			</td>
	  		</tr>
	  		<tr>
	  			<td>
	  				<input type="hidden" id="avata" name="avata" value="<%=dto.getAvata()%>"><br>
	  				<%
	  					for(int i=1;i<=10;i++){%>
	  						<img src="../avata/s<%=i%>.JPG" class="imgphoto" idx="<%=i%>">
	  					<%
	  						if(i==5){%>
	  							<br>
	  						<%}
	  					}
	  				%>
	  				<script type="text/javascript">
	  					//db 에 저장된 이미지에 .select 적용
	  					var avata=$("#avata").val();
	  					$("img").eq(avata-1).addClass("select");
	  					
	  					//아바타 클릭시 idx값을 얻어서 #avata 에 출력
	  					//클릭한 이미지에만 .select 가 적용되도록 하기
	  					$("img.imgphoto").click(function(){
	  						$(this).siblings().removeClass("select");
	  						$(this).addClass("select");
	  						$("#avata").val($(this).attr("idx"));
	  					});
	  					
	  				</script>
	  			</td>	  		
	  		</tr>
	  	</table>
	  </form>
</body>
</html>



