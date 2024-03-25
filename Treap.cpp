#include <vector>
#include <iostream>

template <typename T>
struct Treap {
    struct node {
        T value;
        int cnt, prior, rev, left, right;
    };

    std::vector<node> arr;
    std::vector<int> del;
    int root;

    int newNode(T val, int prior) {
        if (del.empty()) {
            arr.push_back({val, 1, prior, 0, 0, 0});
            return arr.size() - 1;
        }
        int idx = del.back();
        del.pop_back();
        arr[idx] = {val, 1, prior, 0, 0, 0};
        return idx;
    }

    void markForDeletion(int node) {
        if (node == 0) return;
        markForDeletion(arr[node].left);
        markForDeletion(arr[node].right);
        del.push_back(node);
    }

    void print(std::ostream &os, int node) {
        if (node == 0) return;
        print(os, arr[node].left);
        os << arr[node].value << ' ';
        print(os, arr[node].right);
    }

    void push(int v) {
        if (arr[v].rev) {
            arr[v].rev = 0;
            std::swap(arr[v].left, arr[v].right);
            if (arr[v].left != 0) {
                arr[arr[v].left].rev ^= 1;
            }
            if (arr[v].right != 0) {
                arr[arr[v].right].rev ^= 1;
            }
        }
    }

    void pull(int v) {
        if (v == 0) return;
        arr[v].cnt = arr[arr[v].left].cnt + arr[arr[v].right].cnt + 1;
    }

public:
    Treap() {
        root = newNode(T(), 0);
        arr[root].cnt = 0;
    }

    void split(int v, int &l, int &r, int key) {
        if (v == 0) {
            return void (l = r = 0);
        }
        push(v);
        if (arr[arr[v].left].cnt < key) {
            split(arr[v].right, arr[v].right, r, key - arr[arr[v].left].cnt - 1);
            l = v;
        }
        else {
            split(arr[v].left, l, arr[v].left, key);
            r = v;
        }
        pull(v);
    }

    int merge(int l, int r) {
        if (l == 0 || r == 0) return l + r;
        push(l);
        push(r);
        if (arr[l].prior > arr[r].prior) {
            arr[l].right = merge(arr[l].right, r);
            return pull(l), l;
        }
        else {
            arr[r].left = merge(l, arr[r].left);
            return pull(r), r;
        }
    }

    void insert(int pos, T val, int random) {
        int l, r;
        split(root, l, r, pos);
        root = merge(merge(l, newNode(val, random)), r);
    }

    void append(T val, int random) {
        root = merge(root, newNode(val, random));
    }

    void erase(int l, int r) {
        int l, m, r;
        split(root, m, r, r + 1);
        split(m, l, root, l);
        markForDeletion(root);
        root = merge(l, r);
    }

    void reverse(int l, int r) {
        int l, m, r;
        split(root, m, r, r + 1);
        split(m, l, root, l);
        arr[root].rev ^= 1;
        root = merge(merge(l, root), r);
    }

    // k > 0 : right cyclic shift
    // k < 0 : left  cyclic shift
    void cyclicShift(int l, int r, int k) {
        int l, m1, m2, r;
        split(root, m1, r, r + 1);
        split(m1, l, root, l);
        k %= arr[root].cnt;
        if (k < 0) {
            k += arr[root].cnt;
        }
        if (k == 0) {
            root = merge(merge(l, root), r);
            return;
        }
        split(root, m1, m2, arr[root].cnt - k);
        root = merge(merge(l, m2), merge(m1, r));
    }

    T &operator [] (int idx) {
        int l, m, r;
        split(root, m, r, idx + 1);
        split(m, l, root, idx);
        m = root;
        root = merge(merge(l, root), r);
        return arr[m].value;
    }

    friend std::ostream &operator << (std::ostream &os, Treap &t) {
        t.print(os, t.root);
        return os;
    }

    int size() {
        return arr[root].cnt;
    }
};
