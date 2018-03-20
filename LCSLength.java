/*
 * 
 * Aleksander Szewczak
 * 20.03.2018
 * Eclipse
 * Pseudokod ze strony https://inf.ug.edu.pl/~pmp/Z/ASDwyklad/lcs15.pdfs
 */

public class LCSLength {
	
	static String s = "";
	static char[][] b;
	
	public static int Length(String x, String y) {
		int m = x.length();
		int n = y.length();
		int [][] c = new int[m+1][n+1];
		b = new char[m+1][n+1];
		
		for(int i = 0; i <= m; i++)
			c[i][0] = 0;
		
		for(int i = 1; i <= n; i++)
			c[0][i] = 0;
		
		for(int i = 1; i <= m; i++) {
			for(int j = 1; j <= n; j++) {
				if(x.charAt(i-1) == y.charAt(j-1)) {
					c[i][j] = c[i-1][j-1]+1;
					b[i][j] = '/';			
				}
				else if (c[i-1][j] >= c[i][j-1]) {
					c[i][j] = c[i-1][j];
					b[i][j] = '|';
				}
				else {
					c[i][j] = c[i][j-1];
					b[i][j] = '-';
				}
			}
		}
		
		return c[m][n];
	}
	
	public static String PrintLCS(String x, String y, char b[][], int i, int j) {

		if(i == 0 || j == 0) 
			return "";
		
		if(b[i][j] == '/') {
			PrintLCS(x, y, b,i-1,j-1);
			s+=x.charAt(i-1);
		}
		else if(b[i][j] == '|') 
			PrintLCS(x, y, b, i-1, j);
		else
			PrintLCS(x, y, b, i, j-1);
		
		return s;
		
	}
	
	public static void main(String[] args) {
		String x = "aabca"; //test
		String y = "cabba"; //test
		//String x = "abc";
		//String y = "";
		//String x = "abbb";
		//String y = "abfqe";
		
		int i = x.length();
		int j = y.length();
		
		System.out.println("LCSLength: " + Length(x,y));
		System.out.println("PrintLCS: " + PrintLCS(x,y,b,i,j));
	}

}
