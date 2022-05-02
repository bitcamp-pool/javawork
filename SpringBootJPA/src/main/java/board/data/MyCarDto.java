package board.data;

import java.sql.Timestamp;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

import org.hibernate.annotations.CreationTimestamp;

import lombok.Data;


@Entity
@Table(name = "mycar") 	// maycar 테이블이 생성(있다면 수정)
@Data					// Setter, Getter, ToString 모두 포함
public class MyCarDto {
	
	@Id
	@GeneratedValue(strategy = GenerationType.AUTO) // db에 맞게 숫자 자동발생
	private Long num;
	
	@Column(name = "carname")
	private String carname;
	
	@Column(name = "carprice")
	private int carprice;
	
	@Column(name = "carcolor")
	private String carcolor;
	
	@Column(name = "carguip")
	private String carguip;
	
	@CreationTimestamp 								// 엔터티가 생성되는 시점의 시간이 자동등록
	private Timestamp writeday;
}







