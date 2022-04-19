create table stu(
	num smallint auto_increment primary key,
	name varchar(20),
	photo varchar(50),
	hp varchar(20),
	addr varchar(50),
	writeday datetime
);

insert into stu (name, photo, hp, addr, writeday) 
values ('김우빈', '../image/2.jpg', '010-1234-5678', '서울 강남구', now());

insert into stu (name, photo, hp, addr, writeday) 
values ('수지', '../image/19.jpg', '010-5656-5678', '서울 삼성동', now());

insert into stu (name, photo, hp, addr, writeday) 
values ('박보영', '../image/12.jpg', '010-2222-5678', '서울 영등포구', now());

insert into stu (name, photo, hp, addr, writeday) 
values ('신민아', '../image/17.jpg', '010-8888-5678', '제주도 애월읍', now());

insert into stu (name, photo, hp, addr, writeday) 
values ('설현', '../image/15.jpg', '010-9999-5678', '제주도 중문', now());
