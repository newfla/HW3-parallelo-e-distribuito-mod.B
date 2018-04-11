#include <pthread.h>

//Migliore
void mat_mat_ikj(int n, int m, int p, int lda, int ldb, int ldc, double A[][lda], double B[][ldb], double C[][ldc]){
    for(int i=0; i<n; i++){
        for (int k = 0; k < m; k++) {
            for (int j = 0; j < p; j++) {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
}


// struttura di parametri del thread
struct mat_mat_thread_arg{
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
void* mat_mat_thread(void *args){
    struct mat_mat_thread_arg *arg = (struct mat_mat_thread_arg *)args;
    mat_mat_ikj(arg->n, arg->m, arg->p, arg->lda, arg->ldb, arg->ldc, (double (*)[])(arg->A), (double (*)[])(arg->B), (double (*)[])(arg->C));
}

void mat_mat_threads(int ntrow, int ntcol, int n, int m, int p, int lda, int ldb, int ldc, double A[][lda], double B[][ldb], double C[][ldc]){
    pthread_t threads[ntrow*ntcol];
    struct mat_mat_thread_arg args[ntrow*ntcol];
    int me=0, maxChildThread=(ntcol*ntrow)-1;

    // dimensioni delle sottomatrici
    int sub_n = n/ntrow;
    int rest_n = n%ntrow;

    if(rest_n!=0) sub_n++;
    else rest_n = -1;

    int offset_i = 0;

    int thread_number = 0;
    for(int i=0; i<ntrow ; i++){

        int sub_p = p/ntcol;
        int rest_p = p%ntcol;

        if(rest_p!=0) sub_p++;
        else rest_p = -1;
        int offset_j = 0;

        for(int j=0; j<ntcol; j++){
            // parametri del thread
            args[thread_number].n=sub_n;
            args[thread_number].m=m;
            args[thread_number].p=sub_p;
            args[thread_number].lda=lda;
            args[thread_number].ldb=ldb;
            args[thread_number].ldc=ldc;
            args[thread_number].A = &(A[offset_i][0]);
            args[thread_number].B = &(B[0][offset_j]);
            args[thread_number].C = &(C[offset_i][offset_j]);

            // creazione del thread
            pthread_create(threads+thread_number, NULL , mat_mat_thread, args+thread_number);
            thread_number++;

            offset_j += sub_p;

            if(rest_p>0)
                rest_p--;

            if(rest_p==0){
                sub_p--;
                rest_p--;
            }
        }

        offset_i += sub_n;

        if(rest_n>0)
            rest_n--;
        if(rest_n==0){
            sub_n--;
            rest_n--;
        }
    }

    // attesa della terminazione dei threads
    for(int i=0; i<(ntrow*ntcol) ; i++)
        pthread_join(threads[i], NULL);
}



