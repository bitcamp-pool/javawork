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
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
<style type="text/css">
	/*css 영역*/
	
	div.detail {
		margin-top: 100px;
		margin-left: 200px;
		font-size: 25px;
		font-family: 'Jua';
	}
	
</style>
<script type="text/javascript">
  window.onload=function(){
	  init();

		// 메인페이지로 가는 버튼 이벤트
		$("#btnmain").click(function(){
			location.href="ShopJson.html";
			// history.back(); // 이전 페이지로 이동
		});

		// 삭제 버튼 이벤트
		$("#btndelete").click(function(){
			var ans = confirm("삭제하려면 [확인] 버튼을 눌러주세요");
			if(ans){
				/* 요청 [파일로 이동]하면서 num 넘기기(get방식)
				location.href="delete.jsp?num=" + $("#num").val();
				location.href="ShopJson.html"; */

				/* Ajax를 통해 서버와 클라이언트 간 JSON, TEXT, HTML, XML 등 정보를 
				 * *** 화 면 전 환 없이!!! *** 교환
				 */
				$.ajax({
					type:"get",
					data:{"num":$("#num").val()},
					// dataType:"html", // 반환값이 없는 경우 생략 가능?
					url:"delete.jsp",
					success:function(){
						
						// ShopJson.jsp로 이동(목록 갱신)
						location.href="ShopJson.html";
					}
				});
			}
		});

		// 수정 버튼 이벤트
		$("#btnupdate").click(function(){
			$.ajax({
				type:"get",
				dataType:"json",
				url:"DetailJson.jsp",
				data:{"num":$("#num").val()},
				success:function(data){
					$("#usangpum").val(data.sangpum);
					$("#uprice").val(data.price);
					$("#ucnt").val(data.cnt);
					$("#uphoto").val(data.photo);
					$("#umyphoto").attr("src", data.photo);
					$("#uipgoday").val(data.ipgoday);
					$("#ucolor").val(data.color);
				}
			});
			$("#myModal").modal();
		});

		// 부트스트랩 js모달
		// DB 수정 이벤트
		$("#ubtnupdate").click(function(){
			// 전체 폼데이터 읽기
			var fdata = $("#ufrm").serialize();
			// alert(fdata);
			$.ajax({
				type:"post",
				dataType:"html",
				url:"update.jsp",
				data:fdata,
				success:function(){
					location.reload(); // 새로고침
				}
			});
		});


  } // onload END
  
	// 처음 시작시 dto 데이터 넣어주기
	function init(){
		$.ajax({
			type:"get",
			url:"DetailJson.jsp",
			data:{"num":$("#num").val()}, // 입력값(num) 넣어서 url로 보냄
			dataType:"json",							// json타입(객체)으로 리턴받음
			success:function(data){
				$("#photo").attr("src", data.photo);
				$("#photo").css("border", "4px solid gray");
				$("#sangpum").html(data.sangpum);
				$("#color").html(data.color);
				$("#color").css({
					"background-color":data.color,
					"float":"right"
				});
				$("#price").html(data.price + "원");
				$("#cnt").html(data.cnt + "개");
				$("#ipgoday").html(data.ipgoday);
			}
		});
	}
  
</script>
</head>
<%
	String num = request.getParameter("num");
%>

<body>
	<input type="hidden" id="num" value="<%=num%>">
	<div class="detail">
		<table class="table table-bordered" style="width: 700px;">
			<caption><h1>상품상세페이지</h1></caption>
			<tr>
				<td width="300">
					<img src="" width="300" height="400" id="photo" alt="상품이미지">
				</td>
				<td>
					<h2>상품명 : <span id="sangpum"></span></h2>
					<h2>색  상 : <span id="color"></span></h2>
					<h2>가  격 : <span id="price"></span></h2>
					<h2>수  량 : <span id="cnt"></span></h2>
					<h2>입고일 : <span id="ipgoday"></span></h2>
				</td>
			</tr>
			<tr>
				<td colspan="2" align="center">
					<button type="button" class="btn btn-success" 
							style="width: 120px;" id="btnmain">메인</button>
					<button type="button" class="btn btn-info"   
							style="width: 120px;" id="btnupdate">수정</button>
					<button type="button" class="btn btn-danger" 
							style="width: 120px;" id="btndelete">삭제</button>
				</td>
			</tr>
		</table>
	</div>

  <!-- 수정 다이얼로그 Modal -->
  <div class="modal fade" id="myModal" role="dialog">
    <div class="modal-dialog">
    
      <!-- Modal content-->
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal">&times;</button>
          <h4 class="modal-title">상품수정</h4>
        </div>
        <div class="modal-body">
          <!--수정 폼 넣기-->
					<form action="#" id="ufrm" class="form-inline"> <!--사진 옆으로 나오게form-inline-->
						<input type="hidden" id="unum" name="unum" value="<%=num%>">
						<table class="table table-bordered" style="width: 400px;">
							<tr>
								<th bgcolor="pink" style="width: 100px;">상품명</th>
								<td>
									<input type="text" id="usangpum" name="usangpum" class="form-control">
								</td>
							</tr>
							<tr>
								<th bgcolor="pink" style="width: 100px;">상품사진</th>
								<td>
									<select name="uphoto" id="uphoto" class="form-control" style="width: 120px;">
										<script>
											var data=["라운트티", "블랙원피스", "화이트원피스", "도트원피스",
																"블랙조끼", "꽃무늬원피스", "프릴원피스", "반팔원피스", 
																"레이스원피스", "블랙코드", "체크쿠션"];
											var s = "";
											for(i=0; i<=10; i++){
												s+="<option value='../image2/" + (i+1) + ".jpg'>" + data[i] + "</option>";
											}
											document.write(s);
										</script>
									</select>
									<img src="" id="umyphoto" width="60" height="60">
									<script>
										// 1번째 사진넣기
										$("#umyphoto").attr("src", $("#uphoto").val()); 
				
										// 변경시 이벤트
										$("#uphoto").change(function(){
											$("#umyphoto").attr("src", $(this).val());
										});
									</script>
								</td>
							</tr>
							<tr>
								<th bgcolor="pink" style="width: 100px;">색상</th>
								<td>
									<input type="color" id="ucolor" name="ucolor" class="form-control" 
												 value="#ffcccc" style="width: 80px;">
								</td>
							</tr>
							<tr>
								<th bgcolor="pink" style="width: 100px;">단가</th>
								<td>
									<input type="text" id="uprice" name="uprice" class="form-control">
								</td>
							</tr>
							<tr>
								<th bgcolor="pink" style="width: 100px;">수량</th>
								<td>
									<input type="number" id="ucnt" name="ucnt" class="form-control"
												 min="1" max="5" value="1">
								</td>
							</tr>
							<tr>
								<th bgcolor="pink" style="width: 100px;">입고일</th>
								<td>
									<input type="date" id="uipgoday" name="uipgoday" class="form-control"
												 value="2022-04-20">
								</td>
							</tr>
							<tr>
								<td colspan="2" align="center">
									<button type="button" id="ubtnupdate" class="btn btn-info" 
													style="width: 130px;" data-dismiss="modal">DB수정</button>
								</td>
							</tr>
						</table>
					</form>
					<!--수정 폼 넣기-->					
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
        </div>
      </div>
      
    </div>
  </div>

</body>
</html>