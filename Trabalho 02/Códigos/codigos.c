/* (1) Incluir Header file para ter acesso as funções para ter o consumo de energia */
#include "energia.h" 

#include <stdio.h>
#include <stdlib.h>

int max(int a, int b); 
int lcs_c();
int lcs( char *X, char *Y, int m, int n );

/* Dynamic Programming C/C++ implementation of LCS problem */
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs( char *X, char *Y, int m, int n ) 
{ 
int L[m+1][n+1]; 
int i, j; 

/* Following steps build L[m+1][n+1] in bottom up fashion. Note 
    that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
for (i=0; i<=m; i++) 
{ 
    for (j=0; j<=n; j++) 
    { 
    if (i == 0 || j == 0) 
        L[i][j] = 0; 

    else if (X[i-1] == Y[j-1]) 
        L[i][j] = L[i-1][j-1] + 1; 

    else
        L[i][j] = max(L[i-1][j], L[i][j-1]); 
    } 
} 
    
/* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
return L[m][n]; 
} 

/* Utility function to get max of 2 integers */
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

/* Driver program to test above function */
int lcs_c() 
{ 
char X[] = "AGGTAB"; 
char Y[] = "GXTXAYB"; 

int m = strlen(X); 
int n = strlen(Y); 

printf("Length of LCS is %d", lcs( X, Y, m, n ) ); 

return 0; 
} 

int main(int argc, char* argv[])
{
    /* (2) chamar esta funcao no inicio do main para inicializar a lib do RAPL */
    rapl_init();
    
    start_rapl_sysfs(); // (3) Iniciar a contagem de consumo de energia
    clock_t t = clock(); // Iniciar a contagem de tempo
    /*****************************************/
    //LCS

    //Java LCS
    //system("java LCS_code/LongestCommonSubsequence.java");
      
    //C/C++ LCS
    //lcs_c();
    //system("./LCS");

    //Python LCS
    //system("python LCS/LCS.py");

    /*****************************************/
    //LCS Optmized 
   
    //Java LCSopt
    //system("java LCS/LCSopt.java");

    //C/C++ LCSopt
    //system("./LCSopt");

    //Python LCSopt
    //system("python LCS_code/LCSopt.py");
    /*****************************************/

    /*****************************************/
    //Modular Exponentiation 
   
    //Java GFGS
    //system("java GFG/GFG.java");

    //C/C++ GFG
    //system("./GFG");

    //Python GFG
    //system("python GFG_code/GFG.py");
    /*****************************************/
    t = clock() - t; // Finalizar contagem do tempo
    double energy = end_rapl_sysfs();   // (5) Finalizar a contagem dos contadores de energia
    double tempo = ((double)t)/CLOCKS_PER_SEC; // transforma tempo para segundos
    printf("Tempo de execucao em segundos: %.5f\n", tempo);
    printf("Energia consumida em Joules:   %.5f\n", energy); // (6) imprimir consumo de energia em Joules
    
    return 0;
}
