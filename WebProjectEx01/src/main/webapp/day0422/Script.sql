create table guest (
	num smallint auto_increment primary key,
	writer varchar(20),
	pass varchar(10),
	avata varchar(10),
	content varchar(2000),
	writeday datetime
);