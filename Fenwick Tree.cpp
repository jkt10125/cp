#include <vector>
#include <array>

struct FenwickTree : std::vector<std::array<long long, 2>> {
    void update(int t_i, long long val) {
        for (int i = t_i + 1; i <= (int) size(); i += i & -i) {
            (*this)[i - 1][0] += val;
            (*this)[i - 1][1] += val * t_i;
        }
    }
    long long prefixSum(int t_i) {
        long long s0 = 0, s1 = 0;
        for (int i = t_i + 1; i; i -= i & -i) {
            s0 += (*this)[i - 1][0];
            s1 += (*this)[i - 1][1];
        }
        return s0 * t_i - s1;
    }
    FenwickTree() = default;
    FenwickTree(int t_n) : std::vector<std::array<long long, 2>>(t_n, {0, 0}) { }

    void rangeUpdate(int t_l, int t_r, long long val) {
        update(t_l, val);
        update(t_r + 1, -val);
    }

    long long rangeSum(int t_l, int t_r) {
        return prefixSum(t_r + 1) - prefixSum(t_l);
    }
};

struct FenwickTree2D : std::vector<std::vector<long long>> {
    FenwickTree2D(int n, int m) { assign(n, std::vector<long long>(m, 0)); }

    void add(int x, int y, long long v) {
        for (int i = x + 1; i <= size(); i += (i & -i)) {
            for (int j = y + 1; j <= (*this)[i - 1].size(); j += (j & -j)) {
                (*this)[i - 1][j - 1] += v;
            }
        }
    }

    long long prefixSum(int x, int y) {
        long long sum = 0;
        for (int i = x + 1; i; i -= (i & -i)) {
            for (int j = y + 1; j; j -= (j & -j)) {
                sum += (*this)[i - 1][j - 1];
            }
        }
        return sum;
    }


    // assumption: x1 <= x2 and y1 <= y2
    long long rangeSum(int x1, int y1, int x2, int y2) {
        if (x1 > x2) std::swap(x1, x2);
        if (y1 > y2) std::swap(y1, y2);
        return prefixSum(x2, y2) - prefixSum(x1 - 1, y2) - prefixSum(x2, y1 - 1) + prefixSum(x1 - 1, y1 - 1);
    }
};