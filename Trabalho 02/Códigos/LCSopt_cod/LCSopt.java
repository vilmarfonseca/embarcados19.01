// Java Code for A Space Optimized  
// Solution of LCS 
  
class LCSopt { 
      
    // Returns length of LCS  
    // for X[0..m - 1], 
    // Y[0..n - 1]  
    public static int lcs(String X,  
                          String Y) 
    { 
          
        // Find lengths of two strings 
        int m = X.length(), n = Y.length(); 
      
        int L[][] = new int[2][n+1]; 
      
        // Binary index, used to index  
        // current row and previous row. 
        int bi=0; 
      
        for (int i = 0; i <= m; i++) 
        { 
              
            // Compute current binary index 
            bi = i & 1; 
      
            for (int j = 0; j <= n; j++) 
            { 
                if (i == 0 || j == 0) 
                    L[bi][j] = 0; 
      
                else if (X.charAt(i - 1) ==  
                         Y.charAt(j - 1)) 
                    L[bi][j] = L[1 - bi][j - 1] + 1; 
      
                else
                    L[bi][j] = Math.max(L[1 - bi][j],  
                                        L[bi][j - 1]); 
            } 
        } 
      
        // Last filled entry contains length of  
        // LCS for X[0..n-1] and Y[0..m-1]  
        return L[bi][n]; 
    } 
      
      
    // Driver Code  
    public static void main(String[] args)  
    { 
        String X = "AGGTAB"; 
        String Y = "GXTXAYB"; 
      
        System.out.println("Length of LCS is " + 
                                    lcs(X, Y)); 
    } 
} 
