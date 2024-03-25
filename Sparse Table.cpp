#include <vector>

template <typename T, T (*func) (T, T)>
struct DisjointSparseTable {
    std::vector<std::vector<T>> arr;

    DisjointSparseTable(std::vector<int> A) {
        int n = Algorithm::nextPowerOf2(A.size());
        int log = Algorithm::msb(n);
        arr.resize(log + 1, std::vector<T>(n, T()));
        A.resize(n, T());
        arr[0] = A;
        for (int h = 1, range; (range = 1 << h) <= n; ++h) {
            int half = range >> 1;
            for (int i = half; i < n; i += range) {
                arr[h][i - 1] = A[i - 1];
                for (int j = i - 2; j >= i - half; --j) {
                    arr[h][j] = func(A[j], arr[h][j + 1]);
                }
                arr[h][i] = A[i];
                for (int j = i + 1; j < i + half; ++j) {
                    arr[h][j] = func(arr[h][j - 1], A[j]);
                }
            }
        }
    }

    T query(int l, int r) {
        if (l == r) return arr[0][l];
        int h = Algorithm::msb(l ^ r);
        return func(arr[h][l], arr[h][r]);
    }
};