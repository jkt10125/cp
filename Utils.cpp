template <typename T>
inline T nextPowerOf2(T n) {
    T p = 1;
    while (p < n) { p <<= 1; }
    return p;
}

template <typename T>
inline int msb(const T &x) {
    return std::is_same<T, int>::value ? 31 - __builtin_clz(x) : 63 - __builtin_clzll(x);
}

template <typename T>
inline int lsb(const T &x) {
    return (decltype(x) == int) ? __builtin_ctz(x) : __builtin_ctzll(x);
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
