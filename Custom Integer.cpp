template <int p>
struct ModularInt {
    int value;
    static int mod;
 
    constexpr static void setMod(int x) {
        mod = x;
    }
 
    constexpr ModularInt(int x = 0) : value(x) {
        // if (abs(value) >= mod) value %= mod;
        // if (value < 0) value += mod;
    }
 
    explicit constexpr operator int() const {
        return value;
    }
 
    constexpr ModularInt(long long x) : value(x % mod) {
        if (value < 0) value += mod;
    }
 
    constexpr ModularInt& operator += (const ModularInt& other) {
        value += other.value;
        if (value >= mod) value -= mod;
        return *this;
    }
 
    constexpr ModularInt& operator -= (const ModularInt& other) {
        value -= other.value;
        if (value < 0) value += mod;
        return *this;
    }
 
    constexpr ModularInt& operator *= (const ModularInt& other) {
        value = static_cast<int>((value * 1ll * other.value) % mod);
        return *this;
    }
 
    constexpr ModularInt& operator /= (const ModularInt& other) {
        return *this *= other.inverse();
    }
 
    constexpr ModularInt operator + (const ModularInt& other) const {
        return ModularInt(*this) += other;
    }
 
    constexpr ModularInt operator - (const ModularInt& other) const {
        return ModularInt(*this) -= other;
    }
 
    constexpr ModularInt operator * (const ModularInt& other) const {
        return ModularInt(*this) *= other;
    }
 
    constexpr ModularInt operator / (const ModularInt& other) const {
        return ModularInt(*this) /= other;
    }
 
    constexpr ModularInt pow(long long b) const {
        ModularInt ret{1}, a{*this};
        while (b > 0) {
            if (b & 1) ret *= a;
            a *= a;
            b >>= 1;
        }
        return ret;
    }
 
    constexpr ModularInt inverse() const {
        return pow(mod - 2);
    }
 
    constexpr bool operator == (const ModularInt& other) const {
        return value == other.value;
    }
}; // NOTE: remember to set the mod value
 
namespace Combinatorics {
    const int N = 1000007; // size of precomputation
    const int ver = 0; // pick the modint version
    ModularInt<ver> fact[N] = {1}, inv[N] = {1}, ifact[N] = {0};
 
    void init() {
        for (int i = 1; i < N; i++) {
            fact[i] = fact[i - 1] * i;
        }
        ifact[N - 1] = fact[N - 1].inverse();
        for (int i = N - 2; i >= 0; i--) {
            ifact[i] = ifact[i + 1] * (i + 1);
        }
        for (int i = 1; i < N; i++) {
            inv[i] = fact[i - 1] * ifact[i];
        }
    }
 
    ModularInt<ver> C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * ifact[k] * ifact[n - k];
    }
 
    ModularInt<ver> P(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * ifact[n - k];
    }
};
 
using Mint = ModularInt<0>;
 
template <>
int Mint::mod = 998244353;
