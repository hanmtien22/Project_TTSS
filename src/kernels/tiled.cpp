#include <algorithm>
#include "kernels_internal.h"

// nhan khoi co chia o T x T (tiling) de du lieu nam trong cache
// C += A * B
void kernel_tiled(const double* A, const double* B, double* C, int b, int T)
{
    for (int ii = 0; ii < b; ii += T) {
        int i_het = std::min(ii + T, b);   // o cuoi co the nho hon T
        for (int kk = 0; kk < b; kk += T) {
            int k_het = std::min(kk + T, b);
            for (int jj = 0; jj < b; jj += T) {
                int j_het = std::min(jj + T, b);

                // nhan 1 o, giong naive i-k-j nhung chi trong pham vi o
                for (int i = ii; i < i_het; i++) {
                    for (int k = kk; k < k_het; k++) {
                        double a = A[i * b + k];
                        for (int j = jj; j < j_het; j++)
                            C[i * b + j] += a * B[k * b + j];
                    }
                }
            }
        }
    }
}