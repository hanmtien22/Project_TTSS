#pragma once

// khai bao cac kernel, chi dung trong thu muc kernels
void kernel_naive(const double* A, const double* B, double* C, int b);
void kernel_tiled(const double* A, const double* B, double* C, int b, int T);
void kernel_simd(const double* A, const double* B, double* C, int b);