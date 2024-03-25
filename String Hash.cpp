#include <vector>
#include <string>

struct StringHash {
    std::vector<int> suf, b;
    const int mod;

    StringHash(const std::string &s, int base, int _mod) : mod(_mod) {
        int n = s.size();
        suf.assign(n + 1, 0); // suf[n] = 0
        b.assign(n + 1, 1);
        for (int i = n - 1; i >= 0; --i) {
            suf[i] = (suf[i + 1] * 1ll * base + (s[i] - 'a' + 1)) % mod;
            b[n - i] = b[n - i - 1] * 1ll * base % mod;
        }
    }

    int substr(int l, int r) const { // [l, r]
        int v = suf[l] - suf[r + 1] * 1ll * b[r - l + 1] % mod;
        return (v < 0 ? v + mod : v);
    }
};

