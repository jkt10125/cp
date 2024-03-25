#include <bits/stdc++.h>

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

template <typename Info, typename Tag>
struct SegTreeBeats {
private:
    int n;
    std::vector<Info> m_arr;
    std::vector<Tag> m_lazy;

    inline void apply(int t_x, const Tag &t_tag) {
        m_arr[t_x].apply(t_tag);
        if (t_x < n) {
            m_lazy[t_x].apply(t_tag);
        }
    }

    void push(int t_x) {
        if (m_lazy[t_x] == Tag()) return;
        apply(t_x << 1, m_lazy[t_x]);
        apply(t_x << 1 | 1, m_lazy[t_x]);
        m_lazy[t_x] = Tag();
    }

    void pull(int t_x) {
        m_arr[t_x] = Info::merge(m_arr[t_x << 1], m_arr[t_x << 1 | 1]);
    }

public:
    SegTreeBeats(int t_n) : m_arr(n << 1), m_lazy(n), n(nextPowerOf2(t_n)) { }

    void pointUpdate(int t_x, const Info &t_info, int node, int l, int r) {
        if (l == r) {
            m_arr[node] = t_info;
            return;
        }
        int m = (l + r) >> 1;
        push(node);
        if (t_x <= m) {
            pointUpdate(t_x, t_info, node << 1, l, m);
        } else {
            pointUpdate(t_x, t_info, node << 1 | 1, m + 1, r);
        }
        pull(node);
    }

    void pointUpdate(int t_x, const Info &t_info) {
        pointUpdate(t_x, t_info, 1, 0, n - 1);
    }

    void rangeUpdate(int L, int R, const Tag &t_tag, int node, int l, int r) {
        if (l > R || r < L || m_arr[node].max_val <= t_tag.val) {
            return;
        }
        if (l >= L && r <= R && m_arr[node].second_max_val < t_tag.val) {
            apply(node, t_tag);
            return;
        }
        int m = (l + r) >> 1;
        push(node);
        rangeUpdate(L, R, t_tag, node << 1, l, m);
        rangeUpdate(L, R, t_tag, node << 1 | 1, m + 1, r);
        pull(node);
    }

    void rangeUpdate(int L, int R, const Tag &t_tag) {
        rangeUpdate(L, R, t_tag, 1, 0, n - 1);
    }

    Info rangeQuery(int L, int R, int node, int l, int r) {
        if (l > R || r < L) {
            return Info();
        }
        if (L <= l && r <= R) {
            return m_arr[node];
        }
        int m = (l + r) >> 1;
        push(node);
        return Info::merge(rangeQuery(L, R, node << 1, l, m), rangeQuery(L, R, node << 1 | 1, m + 1, r));
    }

    Info rangeQuery(int L, int R) {
        return rangeQuery(L, R, 1, 0, n - 1);
    }
};

struct Tag {
    int val;
    Tag() : val(INT_MAX) { }
    Tag(int t_val) : val(t_val) { }
    void apply(const Tag &t_tag) {
        val = std::min(val, t_tag.val);
    }
    bool operator == (const Tag &rhs) const {
        return val == rhs.val;
    }
};

struct Info {
    int max_val, second_max_val, max_cnt;
    long long sum;
    Info() : max_val(INT_MIN), second_max_val(INT_MIN), max_cnt(0), sum(0) { }
    Info(int t_val) : max_val(t_val), second_max_val(INT_MIN), max_cnt(1), sum(t_val) { }
    void apply(const Tag &t_tag) {
        if (second_max_val < t_tag.val && t_tag.val < max_val) {
            sum -= 1ll * (max_val - t_tag.val) * max_cnt;
            max_val = t_tag.val;
        }
    }
    static Info merge(const Info &lhs, const Info &rhs) {
        Info res;
        if (lhs.max_val > rhs.max_val) {
            res.max_val = lhs.max_val;
            res.max_cnt = lhs.max_cnt;
            res.second_max_val = std::max(lhs.second_max_val, rhs.max_val);
        }
        else if (lhs.max_val < rhs.max_val) {
            res.max_val = rhs.max_val;
            res.max_cnt = rhs.max_cnt;
            res.second_max_val = std::max(rhs.second_max_val, lhs.max_val);
        }
        else {
            res.max_val = lhs.max_val;
            res.max_cnt = lhs.max_cnt + rhs.max_cnt;
            res.second_max_val = std::max(lhs.second_max_val, rhs.second_max_val);
        }
        res.sum = lhs.sum + rhs.sum;
        return res;
    }
};

using namespace std;
void solve() {
    int n, mex = 0;
    cin >> n;
    vector<bool> hsh(n + 1);
    vector<int> A(n);
    SegTreeBeats<Info, Tag> st(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        hsh[A[i]] = 1;
        while (hsh[mex]) { mex++; }
        st.pointUpdate(i, mex);
    }
 
    long long ans = st.rangeQuery(0, n - 1).sum;
 
    for (int i = 0; i < n; i++) {
        st.rangeUpdate(0, n - 1, A[i]);
        st.pointUpdate(i, n);
 
        ans = max(ans, st.rangeQuery(0, n - 1).sum);
    }
 
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

// SegTreeBeats is similiar to normal segtree 
// the only difference comes in the breaking and tagging
// condition check.
