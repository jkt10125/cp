#include <bits/stdc++.h>

typedef int16_t    i16;   typedef uint16_t    u16;
typedef int32_t    i32;   typedef uint32_t    u32;
typedef int64_t    i64;   typedef uint64_t    u64;
typedef __int128_t i128;  typedef __uint128_t u128;

struct Montgomery {
    u64 n, nr;
    
    constexpr Montgomery(u64 n) : n(n), nr(1) {
        // log(2^64) = 6
        for (int i = 0; i < 6; i++) {
            nr *= 2 - n * nr;
        }
    }

    constexpr u64 reduce(u128 x) const {
        u64 q = u64(x) * nr;
        u64 m = ((u128) q * n) >> 64;
        return (x >> 64) + n - m;
        // returns a number in the [0, 2 * n - 2] range
        // (add a "x < n ? x : x - n" type of check if you need a proper modulo)
    }

    constexpr u64 multiply(u64 x, u64 y) const {
        return reduce((u128) x * y);
    }

    constexpr u64 transform(u64 x) const {
        return (u128(x) << 64) % n;
        // can also be implemented as multiply(x, r^2 mod n)
    }

    constexpr u64 pow(u64 a, u64 b) const {
        u64 r = transform(1);
        a = transform(a);

        #pragma GCC unroll 64
        for (int i = 0; i < 64; i++) {
            if (b >> i & 1) {
                r = multiply(r, a);
            }
            a = multiply(a, a);
        }
        return r;
    }

    inline constexpr u64 norm(u64 x) const {
        return x < n ? x : x - n;
    }
} montSpace(1);

bool miller_rabin(u64 n, const std::initializer_list<u64> &base) {
    return std::all_of(base.begin(), base.end(), [n](u64 a) {
        if (n <= a) return true;
        i32 e = __builtin_ctzll(n - 1);
        u64 z = montSpace.pow(a, (n - 1) >> e);
        u64 norm_z = montSpace.norm(montSpace.reduce(z));
        if (norm_z == 1 || norm_z == n - 1) return true;
        while (--e) {
            z = montSpace.multiply(z, z);
            norm_z = montSpace.norm(montSpace.reduce(z));
            if (norm_z == 1) return false;
            if (norm_z == n - 1) return true;
        }
        return false;
    });
}

/* ---------- Prime Precomputation ---------- */
// const i32 N = 10000007;
// const i32 p_N = 664579;

// i32 spf[N], prime[p_N], cnt;

// void sieve() {
//     for (int i = 2; i < N; i++) {
//         if (!spf[i]) {
//             spf[i] = prime[cnt++] = i;
//         }
//         for (int j = 0; j < cnt && prime[j] <= spf[i] && i * prime[j] < N; j++) {
//             spf[i * prime[j]] = prime[j];
//         }
//     }
// }
/* ------------------------------------------ */

bool is_prime(u64 n) {
    // if (n < N) { return spf[n] == n; }
    montSpace = Montgomery(n);
    if (n == 1 || (1 ^ n & 1)) { return n == 2; }
    if (n < u32(-1)) { return miller_rabin(n, {2, 7, 61}); }
    return miller_rabin(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

inline u64 dist(u64 a, u64 b) {
    return a > b ? a - b : b - a;
}

u64 binary_gcd(u64 a, u64 b) {
    if (!a || !b) return (a ^ b);
    u64 shift = __builtin_ctzll(a | b);
    b >>= __builtin_ctzll(b);
    while (a) {
        a >>= __builtin_ctzll(a);
        u64 diff = dist(a, b);
        b = std::min(a, b);
        a = diff;
    }
    return b << shift;
}

std::mt19937_64 gen;

u64 pollard_rho(u64 n) {
    if (1 ^ n & 1) return 2;
    u64 x = gen() % n;
    const i32 M = 128;
    for (int l = M;; l <<= 1) {
        u64 y = x;
        for (int i = 0; i < l; i += M) {
            u64 z = x, p = 1;
            for (int j = 0; j < M; ++j) {
                x = montSpace.multiply(x, x) + 1;
                p = montSpace.multiply(p, dist(x, y));
            }
            if (u64 g = binary_gcd(p, n); g != 1) {
                for (int j = 0; j < M; ++j) {
                    z = montSpace.multiply(z, z) + 1;
                    g = binary_gcd(montSpace.norm(dist(z, y)), n);
                    if (g != 1) return g;
                }
            }
        }
    }
}

u64 find_factor(u64 n, u64 x0 = 2, u64 a = 1) {
    // if (n < N) { return spf[n]; }
    if (is_prime(n)) return n;
    u64 d; do { d = pollard_rho(n); } while (d == n);
    return d;
}

int main() {
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    size_t Q;
    std::cin >> Q;

    while( Q-- ) {
        uint64_t A;
        std::cin >> A;

        std::cout << ( A > 1 && is_prime( A ) ? "Yes" : "No" ) << '\n';
    }
}