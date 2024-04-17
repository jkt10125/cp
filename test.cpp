#include <bits/stdc++.h>

// template <typename int>
struct TrieMap {

    const static int btrie_DEPTH = 31;
    const static int btrie_MAX = 0xffffffff;
    const static int btrie_MIN = 0x00000000;

    // c[2], cnt, par, value
    std::vector<std::array<int, 5>> btrie;
    std::vector<int> del;

    TrieMap() : btrie(1, {0, 0, 0, -1, 0}) { }

    int new_node_impl() {
        int idx = (del.empty()) ? btrie.size() : del.back();
        (del.empty()) ? btrie.push_back({}) : del.pop_back();
        btrie[idx][0] = btrie[idx][1] = btrie[idx][2] = 0;
        return idx;
    }

    void go_up_impl(int &p, int &x) {
        p = btrie[p][3];
        x >>= 1;
    }

    void go_down_impl(int &p, int &x, int b) {
        p = btrie[p][b];
        x = x << 1 | b;
    }

    int find_impl(int p, int &x, int up, int b) {
        if (up) {
            while (!((b ^ (x & 1)) && btrie[btrie[p][3]][b])) {
                go_up_impl(p, x);
                if (p == -1) { return 0; }
            }
            go_up_impl(p, x);
            go_down_impl(p, x, b);
        }
        while (btrie[p][0] | btrie[p][1]) {
            go_down_impl(p, x, b ^ (btrie[p][1 ^ b] != 0));
        }
        return 1;
    }

    int &value_at (int x) {
        x ^= (1 << btrie_DEPTH);
        int p = 0;
        for (int i = btrie_DEPTH; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (!btrie[p][b]) {
                btrie[p][b] = new_node_impl();
                btrie[btrie[p][b]][3] = p;
            }
            p = btrie[p][b];
        }
        if (!btrie[p][2]) {
            for (int tp = p; tp != -1; tp = btrie[tp][3]) {
                btrie[tp][2]++;
            }
            btrie[p][4] = int();
        }
        return btrie[p][4];
    }

    bool erase(int x, int i, int p) {
        x ^= (1 << btrie_DEPTH);
        if (i == -1) {
            return (btrie[p][2]) ? (btrie[p][2]--, 1) : 0;
        }
        int b = (x >> i) & 1;
        if (!btrie[p][b]) { return 0; }
        bool ok = erase(x, i - 1, btrie[p][b]);
        if (ok) {
            btrie[p][2]--;
            if (!btrie[btrie[p][b]][2]) {
                del.push_back(btrie[p][b]);
                btrie[p][b] = 0;
            }
        }
        return ok;
    }

    int get_extreme(int b) {
        int p = 0, res = 0;
        (btrie[0][2]) ? find_impl(p, res, 0, 1 ^ b) : (res = (b) ? btrie_MIN : btrie_MAX);
        return res ^ (1 << btrie_DEPTH);
    }

    int find(int x, int b) {
        x ^= (1 << btrie_DEPTH);
        int p = 0, res = 0;
        for (int i = btrie_DEPTH; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (btrie[p][bit]) {
                p = btrie[p][bit];
                res = res << 1 | bit;
            } else {
                (find_impl(p, res, 1 ^ b ^ bit, b) == 0) ? (res = (b) ? btrie_MIN : btrie_MAX) : 0;
                break;
            }
        }
        return res ^ (1 << btrie_DEPTH);
    }

    int order_of_key(int x) {
        x ^= (1 << btrie_DEPTH);
        int p = 0, res = 0;
        for (int i = btrie_DEPTH; i >= 0; i--) {
            int b = (x >> i) & 1;
            res += b * btrie[btrie[p][0]][2];
            p = btrie[p][b];
            if (!p) { break; }
        }
        return res;
    }

    int find_by_order(int k) {
        int p = 0, res = 0;
        for (int i = btrie_DEPTH; i >= 0; i--) {
            if (btrie[p][0] && btrie[btrie[p][0]][2] > k) {
                p = btrie[p][0];
            } else {
                k -= btrie[btrie[p][0]][2];
                p = btrie[p][1];
                res |= 1 << i;
            }
        }
        return res ^ (1 << btrie_DEPTH);
    }

    int get_max_xor(int x) {
        x ^= (1 << btrie_DEPTH);
        int p = 0, res = 0;
        for (int i = btrie_DEPTH; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (btrie[p][1 ^ b]) {
                p = btrie[p][1 ^ b];
                res |= 1 << i;
            } else {
                p = btrie[p][b];
            }
        }
        return res ^ x;
    }
};

void solve() {
    int n, mex = 0;
    std::cin >> n;
    std::vector<bool> hsh(n + 1);
    std::vector<int> A(n);
    TrieMap mp;
    long long sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
        hsh[A[i]] = 1;
        while (hsh[mex]) { mex++; }
        sum += mex;
        mp.value_at(mex)++;
    }
    ans = sum;
    for (int i = 0; i < n; i++) {
        int min_val = mp.get_extreme(0);
        sum -= min_val;
        mp.value_at(min_val)--;
        if (mp.value_at(min_val) == 0) {
            mp.erase(min_val, mp.btrie_DEPTH, 0);
        }
        mp.value_at(A[i]) = 0;
        int next = mp.find(A[i] + 1, 1);
        while (next != INT_MIN) {
            int second = mp.value_at(next);
            sum -= next * 1ll * second;
            mp.value_at(A[i]) += second;
            sum += A[i] * 1ll * second;
            mp.erase(next++, mp.btrie_DEPTH, 0);
            next = mp.find(next, 1);
        }
        mp.value_at(n) = 1;
        sum += n;
        ans = std::max(ans, sum);
    }
 
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}