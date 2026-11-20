// Tich vo huong song song bang OpenMP
// Cach chay: dot_omp [n] [so_luong]   (mac dinh n = 10^7, so luong = OMP_NUM_THREADS)
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

    std::printf("n = %lld\n", n);
    std::printf("so luong = %d\n", omp_get_max_threads());
    return 0;
}
