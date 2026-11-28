#include <algorithm>
#include "kernels_internal.h"

// ket hop tiling va simd: chia o T x T cho vua cache,
// vong j trong moi o duoc vector hoa bang AVX2
void kernel_tiled_simd(const double* __restrict A, const double* __restrict B,
                       double* __restrict C, int b, int T)
{
    for (int ii = 0; ii < b; ii += T) {
        int i_het = std::min(ii + T, b);
        for (int kk = 0; kk < b; kk += T) {
            int k_het = std::min(kk + T, b);
            for (int jj = 0; jj < b; jj += T) {
                int j_het = std::min(jj + T, b);

                for (int i = ii; i < i_het; i++) {
                    for (int k = kk; k < k_het; k++) {
                        double a = A[i * b + k];
                        #pragma omp simd
                        for (int j = jj; j < j_het; j++)
                            C[i * b + j] += a * B[k * b + j];
                    }
                }
            }
        }
    }
}