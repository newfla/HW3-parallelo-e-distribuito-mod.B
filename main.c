#include <stdio.h>
#include <Utility/utility.h>
#include <stdlib.h>
#include <math.h>
#include <Mat_Mat/mat_mat.h>
#include <memory.h>

#define MAX_N 500
#define MAX_THREADS 4

void execMat_Mat(char* fileName, int n, int ntrow, int ntcol, double*A, double*B, double*C);

int main() {
    char *firstLine="Ntrow_Ntcol;Dimension;Performance",
        *fileName;//="../Test.csv";
    double *A, *B, *C;
    //Creazione file .CSV con intestazione
    //fileName==NULL indica che vado in stdout così non dobbiamo modificare nè il pbs nè il codice ;)
    clean_file(fileName);
    append_to_file(fileName,firstLine);

    //Inizializzazione variabili
    A=(double*)calloc(MAX_N*MAX_N, sizeof(double));
    B=(double*)calloc(MAX_N*MAX_N, sizeof(double));
    C=(double*)calloc(MAX_N*MAX_N, sizeof(double));

    //Riempio le due matrici
    fill_vector(A,MAX_N*MAX_N);
    fill_vector(B,MAX_N*MAX_N);
    
    //Individuo NTROW e NTCOL
    int *divisori=find_divisors(MAX_THREADS);

    //Per dimensioni crescenti dell'input
    for (int j = 5; j <=MAX_N; j+=5) {
        //Per ogni coppia di NTROW e NTCOL (a,b)!=(b,a)
        for (int i = 1; i < divisori[0]; i+=2) {
            execMat_Mat(fileName,j,divisori[i],divisori[i+1],A,B,C);
            if (divisori[i]!=divisori[i+1])
                execMat_Mat(fileName,j,divisori[i+1],divisori[i],A,B,C);
        }

    }
    free(divisori);
    free(A);
    free(B);
    free(C);
    return 0;
}

void execMat_Mat(char* fileName, int n, int ntrow, int ntcol, double*A, double*B, double*C){
    double btime, etime, span;
    char result[50];
    btime = get_cur_time(); //inizio blocco da monitorare
    mat_mat_threads(ntrow,ntcol,n,n,n,MAX_N,MAX_N,MAX_N,(double (*)[])A,(double (*)[])B,(double (*)[])C);
    etime = get_cur_time();  //fine blocco da monitorare
    span=etime-btime;
    span=(2*(pow(n,3)))/span;
    span/=pow(10,9);
    if (!isfinite(span))
        span=0.01;
    sprintf(result,"%d_%d;%d;%.2f",ntrow,ntcol,n,span);
    append_to_file(fileName,result);
    memset(C, 0, sizeof(double)*(MAX_N*MAX_N));
}