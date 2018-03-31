#include <pthread.h>

//Migliore
void mat_mat_ikj(int n, int m, int p, int lda, int ldb, int ldc, double A[][lda], double B[][ldb], double C[][ldc]){
    for(int i=0; i<n; i++){
        for (int k = 0; k < p; k++) {
            for (int j = 0; j < m; j++) {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
}


// struttura di parametri del thread
typedef struct mat_mat_thread_arg{
    int n;
    int m;
    int p;
    int lda;
    int ldb;
    int ldc;
    double *A;
    double *B;
    double *C;
};

// thread per prodotto sottomatrici
void mat_mat_thread(void *args){
    struct mat_mat_thread_arg *arg = (struct mat_mat_thread_arg *)args;
    mat_mat_ikj(arg->n, arg->m, arg->p, arg->lda, arg->ldb, arg->ldc, (double (*)[])(arg->A), (double (*)[])(arg->B), (double (*)[])(arg->C));
}

void mat_mat_threads(int ntrow, int ntcol, int n, int m, int p, int lda, int ldb, int ldc, double A[][lda], double B[][ldb], double C[][ldc]){
    pthread_t threads[ntrow*ntcol];
    struct mat_mat_thread_arg args[ntrow*ntcol];

    // dimensioni delle sottomatrici
    int sub_n = n/ntrow;
    int sub_p = p/ntcol;

    int thread_number = 0;
    for(int i=0; i<ntrow ; i++){
        for(int j=0; j<ntcol; j++){
            // parametri del thread
            args[thread_number].n=sub_n;
            args[thread_number].m=m;
            args[thread_number].p=sub_p;
            args[thread_number].lda=lda;
            args[thread_number].ldb=ldb;
            args[thread_number].ldc=ldc;
            args[thread_number].A = &A[i*sub_n][0];
            args[thread_number].B = &B[0][i*sub_p];
            args[thread_number].C = &C[i*sub_n][j*sub_p];

            // creazione del thread
            pthread_create(threads+thread_number, NULL , mat_mat_thread, args+thread_number);
            thread_number++;
        }
    }

    // attesa della terminazione dei threads
    thread_number = 0;
    for(int i=0; i<ntrow ; i++)
        for(int j=0; j<ntcol; j++)
            pthread_join(threads[thread_number++], NULL);

}


