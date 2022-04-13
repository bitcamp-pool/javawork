-- [JDBC 연결을 위한 테이블 생성 : 계정(bit901)]

-- 1.오라클 DB ------------------------------------------------------------------------

-- 시퀀스 생성
CREATE SEQUENCE seq_bit nocache;

-- 테이블 생성
CREATE TABLE sawon (
	num 		number(5) CONSTRAINT sawon_pk_num PRIMARY KEY,
	name 		varchar2(20),
	buseo 		varchar2(20),
	gibon 		number(10),
	sudang 		number(10),
	writeday 	date
);

-- 자바프로젝트 
-- JDBC 연결하여 데이터 추가 및 조회 기능 구현
select * from sawon order by name;


-- 2.MySQLDB ----------------------------------------------------------------------------

create table person (
	num 		smallint auto_increment primary key,
	name 		varchar(20),
	blood 		varchar(10),
	age 		smallint(5),
	writeday 	datetime
);

-- [계정생성 및 권한 부여하기]
-- root/1234

-- 아이디 + 비밀번호 + host 생성
create user bit901@localhost  identified by 'a1234';
create user bitcamp@localhost identified by 'a1234';

-- localhost만 추가된 계정에 외부 host 접근권한 추가
create user bit901@'%'  identified by 'a1234';
create user bitcamp@'%' identified by 'a1234';

-- 모든 권한부여
-- privileges on [데이터베이스 이름].[테이블 이름] to 계정@localhost or '%' identified by '비밀번호';   
grant all privileges on bit901.*  to bit901@'%'  identified by 'a1234';
grant all privileges on bitcamp.* to bitcamp@'%' identified by 'a1234';


/* 
 * 혈액형별 인원수와 평균 나이 출력(group by)
 * 혈액형	인원수	평균나이
 * A형		2		32(정수로)
 * B형		3		40
 */
select 	blood, 
		count(blood) count, 
		floor(avg(age)) age 
from person 
group by blood;

/*
 * 이름을 입력 후 해당 데이터 삭제
 * 삭제 후 "삭제되었습니다" 메시지 출력
 */
delete from person where name = '홍길동';



