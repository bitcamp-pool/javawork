
-- Oracle JDBC 연습 ----------------------------------------------------------

SELECT * FROM SAWON s;

-- [서치 수행 쿼리]
SELECT 	num, name, buseo, gibon, sudang, gibon + sudang total, 
		TO_CHAR(writeday, 'yyyy-MM-dd hh:mm') writeday 
FROM SAWON 
WHERE name LIKE '%동%';

-- 한줄로 만들기 + 복사 붙여넣기
SELECT 	num, name, buseo, gibon, sudang, gibon + sudang total, TO_CHAR(writeday, 'yyyy-MM-dd hh:mm') writeday FROM SAWON WHERE name LIKE '%이%';


-- [부서정보 쿼리]
SELECT 	buseo, 
		round(avg(gibon + sudang), 0) pay
FROM SAWON
GROUP BY BUSEO;

-- 한줄로 만들기
SELECT 	buseo, round(avg(gibon + sudang), 0) pay FROM SAWON GROUP BY BUSEO;
