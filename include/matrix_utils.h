#pragma once

#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <vector>

using Matrix = std::vector<double>;

inline std::size_t matrix_elements(int n)
{
    // Ming's kernel uses int offsets, and MPI uses int element counts.
    if (n < 1 || n > std::numeric_limits<int>::max() / n) {
        throw std::invalid_argument("matrix side exceeds the supported range");
    }
    return static_cast<std::size_t>(n) * n;
}

inline int ceil_div(int n, int d)
{
    return n / d + (n % d != 0);
}

inline void pack_block(const double* matrix, int n, int row, int col,
                       double* block, int side)
{
    const int rows = std::clamp(n - row, 0, side);
    const int cols = std::clamp(n - col, 0, side);
    if (rows < side || cols < side) {
        std::fill_n(block, side * side, 0.0);
    }
    if (cols == 0) {
        return;
    }
    for (int i = 0; i < rows; ++i) {
        std::copy_n(matrix + (row + i) * n + col, cols, block + i * side);
    }
}

inline void store_block(const double* block, int side, double* matrix, int n,
                        int row, int col, bool add = false)
{
    if (row >= n || col >= n) {
        return;
    }
    const int rows = std::min(side, n - row);
    const int cols = std::min(side, n - col);
    for (int i = 0; i < rows; ++i) {
        const double* source = block + i * side;
        double* dest = matrix + (row + i) * n + col;
        if (add) {
            for (int j = 0; j < cols; ++j) {
                dest[j] += source[j];
            }
        } else {
            std::copy_n(source, cols, dest);
        }
    }
}
