

-- MySQL JDBC 연습 ---------------------------------------------------------

select upper(blood) blood, count(blood) count, round(avg(age), 0) age  
from person p 
group by blood;

select * from person p ;

update person 
set blood = 'AB',
	age   =  56
where num = 10;


