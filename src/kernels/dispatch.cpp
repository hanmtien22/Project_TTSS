#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "kernels.h"
#include "kernels_internal.h"

void block_matmul_add(const double* A, const double* B, double* C,
                      int b, Kernel k, int tile)
{
       switch (k) {
    case Kernel::Naive:
        kernel_naive(A, B, C, b);
        break;
    case Kernel::Tiled:
        if (tile <= 0) tile = 64;   // tranh tile = 0 lam vong lap chay mai
        kernel_tiled(A, B, C, b, tile);
        break;
     case Kernel::Simd:
        kernel_simd(A, B, C, b);
        break;
    case Kernel::TiledSimd:
        if (tile <= 0) tile = 64;
        kernel_tiled_simd(A, B, C, b, tile);
        break;
    default:
        printf("Kernel nay chua lam\n");
        exit(1);
    }
}

Kernel parse_kernel(const char* name)
{
    if (strcmp(name, "naive") == 0) return Kernel::Naive;
    if (strcmp(name, "tiled") == 0) return Kernel::Tiled;
    if (strcmp(name, "simd") == 0) return Kernel::Simd;
    if (strcmp(name, "tiled_simd") == 0) return Kernel::TiledSimd;
    printf("Ten kernel khong hop le: %s\n", name);
    exit(1);
}