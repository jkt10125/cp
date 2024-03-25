#include <vector>
#include <type_traits>
#include <iostream>

template <typename T>
inline int msb(const T &x) {
    return std::is_same<T, int>::value ? 31 - __builtin_clz(x) : 63 - __builtin_clzll(x);
}

#ifdef COMMENT

struct Tag {
    Tag() { }
    Tag(int x) { }
    void apply(const Tag &t) { }
    bool operator == (const Tag &t) { }
    // Always return true in the == operator if you do not want lazy propagation
};

struct Info {
    Info() { }
    Info(int x) { }
    void apply(const Tag &t) { }
    static Info merge(const Info &lhs, const Info &rhs) { }
};

#endif

template <typename Info, typename Tag>
struct SegmentTree {
    int n;
    std::vector<Info> tree;
    std::vector<Tag> lazy;

    SegmentTree(int N) : n(1 << (msb(N - 1) + 1)), tree(2 * n), lazy(2 * n) { }

    void apply(int node, const Tag &t, int size) {
        tree[node].apply(t);
        lazy[node].apply(t);
    }

    void push(int node, int size) {
        if (lazy[node] == Tag()) return;
        apply(2 * node, lazy[node], size / 2);
        apply(2 * node + 1, lazy[node], size / 2);
        lazy[node] = Tag();
    }

    void pull(int node) {
        tree[node] = Info::merge(tree[2 * node], tree[2 * node + 1]);
    }

    void pointUpdate(int idx, const Info &x, int node, int l, int r) {
        if (l == r) {
            tree[node] = x;
            return;
        }
        int m = (l + r) / 2;
        push(node, r - l + 1);
        if (m < idx) pointUpdate(idx, x, 2 * node + 1, m + 1, r);
        else pointUpdate(idx, x, 2 * node, l, m);
        pull(node);
    }

    void pointUpdate(int idx, const Info &x) {
        pointUpdate(idx, x, 1, 0, n - 1);
    }

    void rangeUpdate(int L, int R, const Tag &t, int node, int l, int r) {
        if (r < L || R < l) return;
        if (L <= l && r <= R) {
            apply(node, t, r - l + 1);
            return;
        }
        int m = (l + r) / 2;
        push(node, r - l + 1);
        rangeUpdate(L, R, t, 2 * node, l, m);
        rangeUpdate(L, R, t, 2 * node + 1, m + 1, r);
        pull(node);
    }

    void rangeUpdate(int L, int R, const Tag &t) {
        rangeUpdate(L, R, t, 1, 0, n - 1);
    }

    Info rangeQuery(int L, int R, int node, int l, int r) {
        if (r < L || R < l) return Info();
        if (L <= l && r <= R) {
            return tree[node];
        }
        int m = (l + r) / 2;
        push(node, r - l + 1);
        return Info::merge(rangeQuery(L, R, 2 * node, l, m), rangeQuery(L, R, 2 * node + 1, m + 1, r));
    }

    Info rangeQuery(int L, int R) {
        return rangeQuery(L, R, 1, 0, n - 1);
    }

    template <typename F>
    int findFirst(int L, int R, F pred, int node, int l, int r) {
        if (r < L || R < l || !pred(node)) return -1;
        if (l == r) return l;
        int m = (l + r) / 2;
        push(node, r - l + 1);
        int res = findFirst(L, R, pred, 2 * node, l, m);
        if (res == -1) {
            res = findFirst(L, R, pred, 2 * node + 1, m + 1, r);
        }
        return res;
    }

    template <typename F>
    int findFirst(int L, int R, F pred) {
        return findFirst(L, R, pred, 1, 0, n - 1);
    }

    template <typename F>
    int findLast(int L, int R, F pred, int node, int l, int r) {
        if (r < L || R < l || !pred(node)) return -1;
        if (l == r) return l;
        int m = (l + r) / 2;
        push(node, r - l + 1);
        int res = findLast(L, R, pred, 2 * node + 1, m + 1, r);
        if (res == -1) {
            res = findLast(L, R, pred, 2 * node, l, m);
        }
        return res;
    }

    template <typename F>
    int findLast(int L, int R, F pred) {
        return findLast(L, R, pred, 1, 0, n - 1);
    }

    int findKth(int L, int R, int k, int node, int l, int r) {
        if (r < L || R < l || tree[node].cnt < k) return -1;
        if (l == r) return l;
        int m = (l + r) / 2;
        push(node, r - l + 1);
        int res = findKth(L, R, k, 2 * node, l, m);
        if (res == -1) {
            res = findKth(L, R, k - tree[2 * node].cnt, 2 * node + 1, m + 1, r);
        }
        return res;
    }

    int findKth(int L, int R, int k) {
        return findKth(L, R, k, 1, 0, n - 1);
    }
};
