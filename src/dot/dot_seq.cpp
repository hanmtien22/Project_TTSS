// Tich vo huong tuan tu: s = sum(a[i] * b[i]), i = 0..n-1
// Cach chay: dot_seq [n]   (mac dinh n = 10^7)
#include <cstdio>
#include <cstdlib>
#include <vector>

// Gia tri la boi cua 0.5 va 0.25 nen moi tich, moi tong deu bieu dien
// chinh xac bang double -> moi phien ban (seq/omp/mpi/hybrid) cong theo
// thu tu nao cung ra cung mot ket qua, de so sanh.
static void init_vectors(std::vector<double>& a, std::vector<double>& b) {
    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = 1.0 + (i % 7) * 0.5;
        b[i] = 2.0 - (i % 5) * 0.25;
    }
}

static double dot(const std::vector<double>& a, const std::vector<double>& b) {
    double s = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i)
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

    std::vector<double> a(n), b(n);
    init_vectors(a, b);

    double s = dot(a, b);

    std::printf("n = %lld\n", n);
    std::printf("ket qua = %.6f\n", s);
    return 0;
}
