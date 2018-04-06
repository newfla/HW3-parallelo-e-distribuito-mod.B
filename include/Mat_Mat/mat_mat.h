//
// Created by bizzi on 14/03/18.
//

#ifndef HW0_MAT_MAT_H
#define HW0_MAT_MAT_H

#endif //HW0_MAT_MAT_



//Migliore
void mat_mat_ikj(int n, int m, int p, int lda, int ldb, int ldc, double A[][lda], double B[][ldb], double C[][ldc]);

void* mat_mat_threads(int ntrow, int ntcol, int n, int m, int p, int lda, int ldb, int ldc, double A[][lda], double B[][ldb], double C[][ldc]);

