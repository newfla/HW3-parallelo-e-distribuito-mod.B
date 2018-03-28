
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


void mat_mat_threads(int ntrow, int ntcol, int n, int m, int p, int lda, int ldb, int ldc, double A[][lda], double B[][ldb], double C[][ldc]){

}

