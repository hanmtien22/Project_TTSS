#include "kernels_internal.h"

// giong naive nhung bao compiler vector hoa vong j
// AVX2: 1 lenh tinh 4 so double cung luc
// __restrict: hua A, B, C khong trung vung nho, de compiler dam vector hoa
void kernel_simd(const double* __restrict A, const double* __restrict B,
                 double* __restrict C, int b)
{
    for (int i = 0; i < b; i++) {
        for (int k = 0; k < b; k++) {
            double a = A[i * b + k];
            #pragma omp simd
            for (int j = 0; j < b; j++)
                C[i * b + j] += a * B[k * b + j];
        }
    }
}