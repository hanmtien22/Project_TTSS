// Tich vo huong song song bang OpenMP
// Cach chay: dot_omp [n] [so_luong]   (mac dinh n = 10^7, so luong = OMP_NUM_THREADS)
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <omp.h>

// Khoi tao giong het dot_seq de so sanh ket qua
static void init_vectors(std::vector<double>& a, std::vector<double>& b) {
    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = 1.0 + (i % 7) * 0.5;
        b[i] = 2.0 - (i % 5) * 0.25;
    }
}

// Moi luong cong mot doan, reduction(+:s) gop tong rieng cua cac luong
// lai o cuoi, nen khong can critical/atomic.
static double dot(const std::vector<double>& a, const std::vector<double>& b) {
    const long long n = (long long)a.size();
    double s = 0.0;
    #pragma omp parallel for reduction(+:s) schedule(static)
    for (long long i = 0; i < n; ++i)
        s += a[i] * b[i];
    return s;
}

int main(int argc, char** argv) {
    long long n = 10000000;
    if (argc > 1) n = std::atoll(argv[1]);
    if (n <= 0) {
        std::fprintf(stderr, "n phai > 0\n");
        return 1;
    }
    if (argc > 2) {
        int p = std::atoi(argv[2]);
        if (p <= 0) {
            std::fprintf(stderr, "so luong phai > 0\n");
            return 1;
        }
        omp_set_num_threads(p);
    }

    std::vector<double> a(n), b(n);
    init_vectors(a, b);

    // Dung steady_clock giong dot_seq: omp_get_wtime cua MinGW chi chinh
    // xac den ~1 ms, qua tho voi n nho.
    auto t0 = std::chrono::steady_clock::now();
    double s = dot(a, b);
    auto t1 = std::chrono::steady_clock::now();
    double t = std::chrono::duration<double>(t1 - t0).count();

    std::printf("n = %lld\n", n);
    std::printf("so luong = %d\n", omp_get_max_threads());
    std::printf("ket qua = %.6f\n", s);
    std::printf("thoi gian = %.6f s\n", t);
    return 0;
}
