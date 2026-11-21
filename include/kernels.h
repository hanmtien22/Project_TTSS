#pragma once

// Cac loai kernel nhan khoi
enum class Kernel { Naive, Tiled, Simd, TiledSimd };

// C[b x b] += A[b x b] * B[b x b], luu row-major.
// LUU Y: la CONG DON (+=), khong phai ghi de (=).
void block_matmul_add(const double* A, const double* B, double* C,
                      int b, Kernel k, int tile = 64);

// Doi ten dong lenh ("naive" | "tiled" | "simd" | "tiled_simd") sang enum
Kernel parse_kernel(const char* name);