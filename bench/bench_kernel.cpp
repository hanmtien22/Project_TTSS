#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <chrono>
#include <random>
#include <vector>
#include "kernels.h"

// nhan ghi lai cau hinh bien dich, truyen vao luc build: -DCAUHINH=O2
#ifndef CAUHINH
#define CAUHINH khong_ro
#endif
#define STR2(x) #x
#define STR(x) STR2(x)

int main(int argc, char** argv)
{
    const char* ten = "naive";
    int n = 512, tile = 64, reps = 5;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--header") == 0) {
            printf("kernel,n,tile,reps,mean_s,std_s,gflops,checksum,cauhinh\n");
            return 0;
        }
        if (strcmp(argv[i], "--kernel") == 0) ten = argv[++i];
        if (strcmp(argv[i], "--n") == 0) n = atoi(argv[++i]);
        if (strcmp(argv[i], "--tile") == 0) tile = atoi(argv[++i]);
        if (strcmp(argv[i], "--reps") == 0) reps = atoi(argv[++i]);
    }
    Kernel k = parse_kernel(ten);

    // tao A, B ngau nhien (seed co dinh)
    std::vector<double> A(n * n), B(n * n), C(n * n);
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < n * n; i++) {
        A[i] = dist(gen);
        B[i] = dist(gen);
    }

    // chay thu 1 lan cho nong may, khong tinh
    std::fill(C.begin(), C.end(), 0.0);
    block_matmul_add(A.data(), B.data(), C.data(), n, k, tile);

    std::vector<double> t(reps);
    for (int r = 0; r < reps; r++) {
        std::fill(C.begin(), C.end(), 0.0); // kernel cong don nen phai reset C
        auto t0 = std::chrono::steady_clock::now();
        block_matmul_add(A.data(), B.data(), C.data(), n, k, tile);
        auto t1 = std::chrono::steady_clock::now();
        t[r] = std::chrono::duration<double>(t1 - t0).count();
    }

    double tb = 0, ss = 0;
    for (int r = 0; r < reps; r++) tb += t[r];
    tb /= reps;
    for (int r = 0; r < reps; r++) ss += (t[r] - tb) * (t[r] - tb);
    double dlc = reps > 1 ? sqrt(ss / (reps - 1)) : 0;

    double gflops = 2.0 * n * n * (double)n / (tb * 1e9);

    // in checksum de compiler khong bo qua phep nhan
    double cs = 0;
    for (int i = 0; i < n * n; i++) cs += C[i];

    printf("%s,%d,%d,%d,%.6f,%.6f,%.3f,%.6e,%s\n",
           ten, n, tile, reps, tb, dlc, gflops, cs, STR(CAUHINH));
    return 0;
}