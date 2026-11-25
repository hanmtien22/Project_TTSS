#include <cstdio>
#include <cmath>
#include "kernels.h"

int main()
{
    // A = [1 2; 3 4], B = [5 6; 7 8]
    double A[4] = {1, 2, 3, 4};
    double B[4] = {5, 6, 7, 8};
    double C[4] = {0, 0, 0, 0};

    // ket qua tinh tay: A*B = [19 22; 43 50]
    double dung[4] = {19, 22, 43, 50};

    block_matmul_add(A, B, C, 2, Kernel::Naive);
    for (int i = 0; i < 4; i++) {
        if (fabs(C[i] - dung[i]) > 1e-12) {
            printf("Sai o lan 1, vi tri %d: %f\n", i, C[i]);
            return 1;
        }
    }

    // goi them lan nua, vi la cong don nen C phai gap doi
    block_matmul_add(A, B, C, 2, Kernel::Naive);
    for (int i = 0; i < 4; i++) {
        if (fabs(C[i] - 2 * dung[i]) > 1e-12) {
            printf("Sai cong don, vi tri %d: %f\n", i, C[i]);
            return 1;
        }
    }

    printf("OK: naive tinh dung va cong don dung\n");
    return 0;
}