#include <bits/stdc++.h>

// template <typename int>
struct TrieMap {

    const static int btrie_DEPTH = 31;
    const static int btrie_MAX = 0xffffffff;
    const static int btrie_MIN = 0x00000000;
    const static int BTRIE_NODES = 1000000;

    struct node {
        int c[2];
        int cnt, par;
        int value;
    };

    node btrie[BTRIE_NODES];

    int del[BTRIE_NODES];
    int btrie_node_ctr = 1, btrie_del_ctr = 0;

    TrieMap() {
        std::cout << "hello" << std::endl;
        btrie[0].par = -1;
        btrie[0].c[0] = btrie[0].c[1] = btrie[0].cnt = 0;
        btrie_node_ctr = 1, btrie_del_ctr = 0;
    }

    int new_node_impl() {
        int idx = (btrie_del_ctr) ? del[--btrie_del_ctr] : btrie_node_ctr++;
        btrie[idx].c[0] = btrie[idx].c[1] = btrie[idx].cnt = 0;
        return idx;
    }

    void go_up_impl(int &p, int &x) {
        p = btrie[p].par;
        x >>= 1;
    }

    void go_down_impl(int &p, int &x, int b) {
        p = btrie[p].c[b];
        x = x << 1 | b;
    }

    int find_impl(int p, int &x, int up, int b) {
        if (up) {
            while (!((b ^ (x & 1)) && btrie[btrie[p].par].c[b])) {
                go_up_impl(p, x);
                if (p == -1) { return 0; }
            }
            go_up_impl(p, x);
            go_down_impl(p, x, b);
        }
        while (btrie[p].c[0] | btrie[p].c[1]) {
            go_down_impl(p, x, b ^ (btrie[p].c[1 ^ b] != 0));
        }
        return 1;
    }

    int &value_at (int x) {
        x ^= (1 << btrie_DEPTH);
        int p = 0;
        for (int i = btrie_DEPTH; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (!btrie[p].c[b]) {
                btrie[p].c[b] = new_node_impl();
                btrie[btrie[p].c[b]].par = p;
            }
            p = btrie[p].c[b];
        }
        if (!btrie[p].cnt) {
            for (int tp = p; tp != -1; tp = btrie[tp].par) {
                btrie[tp].cnt++;
            }
            btrie[p].value = int();
        }
        return btrie[p].value;
    }

    bool erase(int x, int i, int p) {
        x ^= (1 << btrie_DEPTH);
        if (i == -1) {
            return (btrie[p].cnt) ? (btrie[p].cnt--, 1) : 0;
        }
        int b = (x >> i) & 1;
        if (!btrie[p].c[b]) { return 0; }
        bool ok = erase(x, i - 1, btrie[p].c[b]);
        if (ok) {
            btrie[p].cnt--;
            if (!btrie[btrie[p].c[b]].cnt) {
                del[btrie_del_ctr++] = btrie[p].c[b];
                btrie[p].c[b] = 0;
            }
        }
        return ok;
    }

    int get_extreme(int b) {
        int p = 0, res = 0;
        (btrie[0].cnt) ? find_impl(p, res, 0, 1 ^ b) : (res = (b) ? btrie_MIN : btrie_MAX);
        return res ^ (1 << btrie_DEPTH);
    }

    int find(int x, int b) {
        x ^= (1 << btrie_DEPTH);
        int p = 0, res = 0;
        for (int i = btrie_DEPTH; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (btrie[p].c[bit]) {
                p = btrie[p].c[bit];
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
            res += b * btrie[btrie[p].c[0]].cnt;
            p = btrie[p].c[b];
            if (!p) { break; }
        }
        return res;
    }

    int find_by_order(int k) {
        int p = 0, res = 0;
        for (int i = btrie_DEPTH; i >= 0; i--) {
            if (btrie[p].c[0] && btrie[btrie[p].c[0]].cnt > k) {
                p = btrie[p].c[0];
            } else {
                k -= btrie[btrie[p].c[0]].cnt;
                p = btrie[p].c[1];
                res |= 1 << i;
            }
        }
        return res ^ (1 << btrie_DEPTH);
    }
};

int main() {
    TrieMap trie{};
    std::cout << "hello" << std::endl;
    // trie.value_at(1) = 1;
    // trie.value_at(4) = 4;
    // trie.value_at(3) = 3;
    // trie.value_at(2) = 2;
    return 0;
}