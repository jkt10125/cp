#include <vector>

template <typename T>
inline T nextPowerOf2(T n) {
    T p = 1;
    while (p < n) { p <<= 1; }
    return p;
}

template <typename T>
int pow(int a, T b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = (int) (res * 1ll * a % mod);
        }
        a = (int) (a * 1ll * a % mod);
        b >>= 1;
    }
    return res;
}

int inverse(int a, int mod) {
    return pow(a, mod - 2, mod);
}

const int mod = 998244353;
const int ROOT = 15311432;
const int ROOT_1 = 469870224;
const int ROOT_PW = 1 << 23;

void ntt(std::vector<int> &A, int inv) {
    const int N = (int) A.size();
    for (int i = 1, j = 0; i < N; ++i) {
        int bit = N >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            std::swap(A[i], A[j]);
        }
    }

    for (int len = 2; len <= N; len <<= 1) {
        int wlen = inv ? ROOT_1 : ROOT;
        for (int i = len; i < ROOT_PW; i <<= 1) {
            wlen = (int) (1LL * wlen * wlen % mod);
        }
        for (int i = 0; i < N; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; ++j) {
                int u = A[i + j], v = (int) (1LL * A[i + j + len / 2] * w % mod);
                A[i + j] = u + v < mod ? u + v : u + v - mod;
                A[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int) (1LL * w * wlen % mod);
            }
        }
    }

    if (inv) {
        int N_1 = inverse(N, mod);
        for (int i = 0; i < N; ++i) {
            A[i] = (int) (1LL * A[i] * N_1 % mod);
        }
    }
}

// A = A * B
void multiply(std::vector<int> A, std::vector<int> B) {
    const int N = nextPowerOf2((int) (A.size() + B.size()));
    A.resize(N, 0);
    B.resize(N, 0);
    ntt(A, false);
    ntt(B, false);
    for (int i = 0; i < N; ++i) {
        A[i] = (int) (1LL * A[i] * B[i] % mod);
    }
    ntt(A, true);
}
