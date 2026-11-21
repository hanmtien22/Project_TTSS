#include "kernels_internal.h"

// nhan khoi kieu co ban, thu tu vong lap i-k-j
// C += A * B (cong don vao C, khong ghi de)
void kernel_naive(const double* A, const double* B, double* C, int b)
{
    for (int i = 0; i < b; i++) {
        for (int k = 0; k < b; k++) {
            double a = A[i * b + k];
            for (int j = 0; j < b; j++)
                C[i * b + j] += a * B[k * b + j];
        }
    }
}