#include <vector>
#include <iostream>
using namespace std;

#pragma GCC optimize("Ofast")

template <typename T>
inline int msb(const T &x) {
    return std::is_same<T, int>::value ? 31 - __builtin_clz(x) : 63 - __builtin_clzll(x);
}

#ifdef COMMENT

struct Tag {
    Tag() { }
    Tag(... param) { }
    void apply(const Tag &t) { }
    bool operator == (const Tag &t) { }
    // Always return true in the == operator if you do not want lazy propagation
};

struct Info {
    Info() { }
    Info(... param) { }
    void apply(const Tag &t) { }
    static Info merge(const Info &lhs, const Info &rhs) { }
    // Be careful! the default value of Info might not be the identity element of merge
};

const int N = 10000007; // JUST IN LIMIT OF 256 MB MEMORY
struct node_t {
    Info info;
    Tag lazy;
    int left, right;
    node_t() : info(), lazy(), left(0), right(0) { }
    node_t(const Info &info, const Tag &lazy, int left, int right) : info(info), lazy(lazy), left(left), right(right) { }
} arr[N];

#endif

int ctr = 1;
std::vector<int> root;

struct PersistentSegTree {

    int n;
    node_t *tree;

    PersistentSegTree(int N, node_t arr[]) : n(1 << (msb(N - 1) + 1)), tree(arr) {
        for (int i = n - 1; i; i--) {
            tree[i].left = i << 1;
            tree[i].right = i << 1 | 1;
            pull(i);
        }
        ctr = 2 * n;
        root.assign(1, 1);
    }

    int newNode(int node) {
        tree[ctr] = tree[node];
        return ctr++;
    }

    int newNode(const node_t &node) {
        tree[ctr] = node;
        return ctr++;
    }

    void apply(int node, const Tag &tag, int size) {
        tree[node].info.apply(tag, size);
        tree[node].lazy.apply(tag);
    }

    void push(int node, int size) {
        if (tree[node].lazy == Tag()) return;
        tree[node].left = newNode(tree[node].left);
        tree[node].right = newNode(tree[node].right);
        apply(tree[node].left, tree[node].lazy, size / 2);
        apply(tree[node].right, tree[node].lazy, size / 2);
        tree[node].lazy = Tag();
    }

    void pull(int node) {
        tree[node].info = Info::merge(tree[tree[node].left].info, tree[tree[node].right].info);
    }

    int pointUpdate(int idx, const Info &info, int node, int l, int r) {
        if (l == r) {
            // change this line to change the type of update
            return newNode({info, {}, 0, 0});
            // return newNode({Info::merge(tree[node].info, info), Tag(), 0, 0});
        }
        int m = (l + r) / 2;
        push(node, r - l + 1);
        int nNode = newNode({{}, {}, tree[node].left, tree[node].right});
        if (m < idx) tree[nNode].right = pointUpdate(idx, info, tree[node].right, m + 1, r);
        else tree[nNode].left = pointUpdate(idx, info, tree[node].left, l, m);
        pull(nNode);
        return nNode;
    }

    int pointUpdate(int idx, const Info &info, int node) {
        return pointUpdate(idx, info, node, 0, n - 1);
    }

    int rangeUpdate(int L, int R, const Tag &tag, int node, int l, int r) {
        if (r < L || R < l) return node;
        if (L <= l && r <= R) {
            int nNode = newNode(node);
            apply(nNode, tag, r - l + 1);
            return nNode;
        }
        int m = (l + r) / 2;
        push(node, r - l + 1);
        int nNode = newNode(0);
        tree[nNode].left = rangeUpdate(L, R, tag, tree[node].left, l, m);
        tree[nNode].right = rangeUpdate(L, R, tag, tree[node].right, m + 1, r);
        pull(nNode);
        return nNode;
    }

    int rangeUpdate(int L, int R, const Tag &tag, int node) {
        return rangeUpdate(L, R, tag, node, 0, n - 1);
    }

    Info rangeQuery(int L, int R, int node, int l, int r) {
        if (r < L || R < l) return Info();
        if (L <= l && r <= R) {
            return tree[node].info;
        }

        int m = (l + r) / 2;
        push(node, r - l + 1);
        return Info::merge(rangeQuery(L, R, tree[node].left, l, m), rangeQuery(L, R, tree[node].right, m + 1, r));
    }

    Info rangeQuery(int L, int R, int node) {
        return rangeQuery(L, R, node, 0, n - 1);
    }

    template <typename F>
    int findFirst(int L, int R, const F &pred, int node, int l, int r) {
        if (r < L || R < l || !pred(tree[node].info)) return -1;
        if (l == r) return l;
        int m = (l + r) / 2;
        push(node, r - l + 1);
        int res = findFirst(L, R, pred, tree[node].left, l, m);
        if (res == -1) {
            res = findFirst(L, R, pred, tree[node].right, m + 1, r);
        }
        return res;
    }

    template <typename F>
    int findFirst(int L, int R, const F &pred, int node) {
        return findFirst(L, R, pred, node, 0, n - 1);
    }

    template <typename F>
    int findLast(int L, int R, const F &pred, int node, int l, int r) {
        if (r < L || R < l || !pred(tree[node].info)) return -1;
        if (l == r) return l;
        int m = (l + r) / 2;
        push(node, r - l + 1);
        int res = findLast(L, R, pred, tree[node].right, m + 1, r);
        if (res == -1) {
            res = findLast(L, R, pred, tree[node].left, l, m);
        }
        return res;
    }

    template <typename F>
    int findLast(int L, int R, const F &pred, int node) {
        return findLast(L, R, pred, node, 0, n - 1);
    }

    // int findKth(int L, int R, int k, int node, int l, int r) {
    //     if (r < L || R < l || tree[node].info.cnt < k) return -1;
    //     if (l == r) return l;
    //     int m = (l + r) / 2;
    //     push(node, r - l + 1);
    //     int res = findKth(L, R, k, tree[node].left, l, m);
    //     if (res == -1) {
    //         res = findKth(L, R, k - tree[tree[node].left].info.cnt, tree[node].right, m + 1, r);
    //     }
    //     return res;
    // }

    // int findKth(int L, int R, int k, int node) {
    //     return findKth(L, R, k, node, 0, n - 1);
    // }
};
