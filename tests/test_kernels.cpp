#include <cstdio>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include "kernels.h"

// chay naive va kernel k tren cung du lieu, tra ve sai so lon nhat
double so_sanh(int b, Kernel k, int tile)
{
    std::vector<double> A(b * b), B(b * b), C1(b * b), C2(b * b);
    std::mt19937 gen(123);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    for (int i = 0; i < b * b; i++) {
        A[i] = dist(gen);
        B[i] = dist(gen);
        C1[i] = dist(gen);   // C ban dau khac 0 de kiem tra cong don
    }
    C2 = C1;

    block_matmul_add(A.data(), B.data(), C1.data(), b, Kernel::Naive);
    block_matmul_add(A.data(), B.data(), C2.data(), b, k, tile);

    double sai = 0;
    for (int i = 0; i < b * b; i++)
        sai = std::max(sai, fabs(C1[i] - C2[i]));
    return sai;
}

int main()
{
    int cac_b[] = {1, 7, 33, 64, 100, 129, 1000};
    int cac_tile[] = {16, 32, 64, 128};
    int loi = 0;

    for (int b : cac_b) {
        for (int tile : cac_tile) {
            double sai = so_sanh(b, Kernel::Tiled, tile);
            double nguong = 1e-9 * b;   // theo quy dinh cua nhom
            printf("tiled b=%4d tile=%3d sai so=%.3e %s\n",
                   b, tile, sai, sai <= nguong ? "ok" : "LOI");
            if (sai > nguong) loi++;
        }
    }
    for (int b : cac_b) {
        double sai = so_sanh(b, Kernel::Simd, 0);
        double nguong = 1e-9 * b;
        printf("simd  b=%4d          sai so=%.3e %s\n",
               b, sai, sai <= nguong ? "ok" : "LOI");
        if (sai > nguong) loi++;
    }
    if (loi == 0) printf("OK: tiled va simd khop naive\n");
    else printf("Co %d truong hop loi\n", loi);
    return loi > 0;
}