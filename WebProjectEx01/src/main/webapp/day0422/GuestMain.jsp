<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
<script src="https://code.jquery.com/jquery-3.5.0.js"></script>   
<link href="https://fonts.googleapis.com/css2?family=Gamja+Flower&family=Jua&family=Lobster&family=Nanum+Pen+Script&display=swap" rel="stylesheet">
<style type="text/css">
	div.header {
		width: 80%;
		height: 110px;
		line-height: 110px;
		text-align: center;
		font-size: 35px;
		font-family: 'Lobster';
		font-weight: bold;
		border: 10px solid gold;
		margin-bottom: 30px;
	}
	div.all {
		width: 1100px;
	}
	div.inform {
		font-size: '20px';
		font-family: 'Jua';
		float: left;
		width: 480px;
		height: auto;
		border: 5px solid gray;
		padding: 20px 20px;
	}
	div.list {
		font-size: '20px';
		font-family: 'Jua';
		float:right;	
		width: 600px;
		height: auto;
		border: 5px solid gray;
		padding: 20px 20px;
	}
	img.imgphoto {
		width: 55px;
		height: 55px;
		margin-right: 3px;
		cursor: pointer;
	}
	.select {
		border: 2px solid black;
		box-show: 3px 3px 3px gray;
	}
</style>
<script type="text/javascript">
	$(function() {
		// 시작 시 목록 출력
		list(); 
		// 저장 이벤트
		$(".btnsave").click(function(){
			// 폼 전체 데이터를 읽어서 inster.jsp로 보낸다
			// 성공 후 list() 다시 호출 후, 입력값 초기화
			var fdata = $("#frm").serialize();
			$.ajax({
				type:"post",
				data:fdata,
				url:"insert.jsp",
				dataType:"html",
				success:function(){
					list();
					// 화면갱신(초기화)
					$("#writer").val("");
					$("#pass").val("");
					$("#content").val("");
					
					$("#avata").val("1");
					$("img.imgphoto:first").removeClass("select");
					$("img.imgphoto:first").addClass("select");
				}
			});
		});
	});
	
	function list() {
		$.ajax({
			method:"get",
			url:"list.jsp",
			dataType:"json",
			success:function(data){
				
			}
		});
	}
</script>
</head>
<body>
<div class="header">
	Guest Ajax Test
</div>
<div class="all">
	<div class="inform">
	  <form id="frm" class="form-inline">
	  	<table class="table">
	  		<tr>
		  		<td width="350">
		  		  작성자 : <input type="text"     id="writer" name="writer" 
		  		                  class="form-control" style="width: 100px;">
		  		  비번 :   <input type="password" id="pass"   name="pass" 
		  		  				  class="form-control" style="width: 100px;">          
		  		</td>
		  		<td class="btnsave" rowspan="3" style="cursor:pointer; background-color:orange;"
		  		 	align="center" valign="middle">
		  			저장
		  		</td>
	  		</tr>
	  		<tr>
	  			<td>
	  				<textarea id="content" name="content" style="width:100%; height:80px;"></textarea>
	  			</td>
	  		</tr>
	  		<tr>
	  			<td>
	  				<!-- 아래태그는 브라우저로 선택한 아바타의 번호가 정상적으로 출력 확인 후 hidden으로 바꾼다 -->
	  				<!-- <input type="text" id="avata" name="avata" value="1"><br>  -->
	  				<input type="hidden" id="avata" name="avata" value="1"><br>
	  				<%
	  					for(int i=1; i<=10; i++){%>
	  					<img src="../avata/s<%=i%>.JPG" class="imgphoto" idx="<%=i%>">
	  					<%
	  						if(i==5){%>
	  							<br>
	  						<%}
	  					}
	  				%>
	  				<script>
	  					// 첫번째 이미지에 .select 적용
	  					$("img.imgphoto").eq(0).addClass("select");
	  					// 아바타 클릭시 idx값을 얻어서 #avata에 출력
	  					// 클릭한 이미지에만 .select가 적용되도록 하기
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
	</div>
	
	<div class="list">
	123
	</div>
</div>
</body>
</html>
