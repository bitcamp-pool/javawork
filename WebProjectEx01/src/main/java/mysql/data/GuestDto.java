package mysql.data;

import java.sql.Timestamp;

public class GuestDto {
	
	private String num;
	private String writer;
	private String pass;
	private String avata;
	private String content;
	private Timestamp writeday;
	
	public GuestDto() {
		
	}
	
	public GuestDto(String writer, String pass, String avata, String content) {
		this.writer = writer;
		this.pass = pass;
		this.avata = avata;
		this.content = content;
	}

	public GuestDto(String num, String writer, String pass, String avata, String content) {
		this.num = num;
		this.writer = writer;
		this.pass = pass;
		this.avata = avata;
		this.content = content;
	}

	public String getNum() {
		return num;
	}

	public void setNum(String num) {
		this.num = num;
	}

	public String getWriter() {
		return writer;
	}

	public void setWriter(String writer) {
		this.writer = writer;
	}

	public String getPass() {
		return pass;
	}

	public void setPass(String pass) {
		this.pass = pass;
	}

	public String getAvata() {
		return avata;
	}

	public void setAvata(String avata) {
		this.avata = avata;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	public java.sql.Timestamp getWriteday() {
		return writeday;
	}

	public void setWriteday(java.sql.Timestamp writeday) {
		this.writeday = writeday;
	}

}
