/* (1) Incluir Header file para ter acesso as funções para ter o consumo de energia */
#include "energia.h" 

int main(int argc, char* argv[])
{
    /* (2) chamar esta funcao no inicio do main para inicializar a lib do RAPL */
    rapl_init();
    
	start_rapl_sysfs(); // (3) Iniciar a contagem de consumo de energia
    clock_t t = clock(); // Iniciar a contagem de tempo
        /* (4) Chamar aqui a função que faz o que você deseja medir o tempo e a energia */
    system("java Java/LongestCommonSubsequence");
        /*************************************************/
    t = clock() - t; // Finalizar contagem do tempo
    double energy = end_rapl_sysfs();   // (5) Finalizar a contagem dos contadores de energia
    double tempo = ((double)t)/CLOCKS_PER_SEC; // transforma tempo para segundos
    printf("Tempo de execucao em segundos: %.5f\n", tempo);
    printf("Energia consumida em Joules:   %.5f\n", energy); // (6) imprimir consumo de energia em Joules
    
	return 0;
}
