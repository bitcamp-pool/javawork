package study2;

public class Score {

	private int kor, eng, mat;
	
	public Score(int kor) {
		this.kor = kor;
	}
	
	public void setEng(int eng) {
		this.eng = eng;
	}
	
	public void setMat(int mat) {
		this.mat = mat;
	}
	
	public String getScore() {
		String s = "국어: " + kor + ", 영어: " + eng + ", 수학: " + mat; 
		return s;
	}
}
