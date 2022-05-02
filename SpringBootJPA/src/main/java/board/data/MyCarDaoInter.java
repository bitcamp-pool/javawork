package board.data;

import org.springframework.data.jpa.repository.JpaRepository;
//import org.springframework.data.repository.CrudRepository;

/* 2개의 인터페이스가 있다.
 * CrudRepository 
 * JpaRepository
 */

public interface MyCarDaoInter extends JpaRepository<MyCarDto, Long>{
	
	
}
