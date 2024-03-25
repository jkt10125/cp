#include <vector>
#include <functional>

// Euler Tour: returns a vector of pairs (in, out) for each node
std::vector<std::array<int, 2>> eularTour(const std::vector<std::vector<int>> &A, int root) {
    std::vector<std::array<int, 2>> res(A.size());
    int timer = 0;
    std::function<void(int, int)> dfs = [&] (int x, int p) {
        res[x][0] = timer++;
        for (int y : A[x]) {
            if (y != p) {
                dfs(y, x);
            }
        }
        res[x][1] = timer++;
    };
    return dfs(root, -1), res;
}

class treeAncestor {
    int n, log;
    std::vector<int> lvl;
    std::vector<std::vector<int>> maxe, lift;

public:
    // Constructor which takes the weighted undirected tree as input 
    treeAncestor(std::vector<std::vector<std::array<int, 2>>> &A, int root) {
        n = (int) A.size();
        log = std::__lg(n) + 1;
        lvl.resize(n);
        lift.resize(log, std::vector<int>(n));
        maxe.resize(log, std::vector<int>(n));

        std::function<void(int, int)> dfs = [&] (int x, int p) {
            lvl[x] = (p != -1) ? lvl[p] + 1 : 0;
            lift[0][x] = p;
            for (int i = 1; i < log; i++) {
                lift[i][x] = (lift[i - 1][x] != -1) ? lift[i - 1][lift[i - 1][x]] : -1;
                maxe[i][x] = std::max(maxe[i - 1][x], (lift[i - 1][x] != -1) ? maxe[i - 1][lift[i - 1][x]] : 0);
            }
            for (auto &[y, w] : A[x]) {
                if (y != p) {
                    maxe[0][y] = w;
                    dfs(y, x);
                }
            }
        };
        dfs(root, -1);
    }
    
    // Constructor which takes parent and weight array separately
    // REQ: par[root] == -1
    treeAncestor(std::vector<int> &par, std::vector<int> &W) {
        n = (int) par.size();
        int root = 0;
        while (root < n && par[root] != -1) { root++; }
        std::vector<std::vector<std::array<int, 2>>> A(n);
        for (int i = 1; i < n; i++) {
            A[par[i]].push_back({i, W[i]});
            A[i].push_back({par[i], W[i]});
        }
        *this = treeAncestor(A, root);
    }

    int kthAncestor(int x, int k) {
        for (int i = log - 1; i >= 0; i--) {
            if (k & (1 << i)) { x = lift[i][x]; }
        }
        return x;
    }

    int lca(int x, int y) {
        if (lvl[x] < lvl[y]) { std::swap(x, y); }
        x = kthAncestor(x, lvl[x] - lvl[y]);
        if (x == y) { return x; }
        for (int i = log - 1; i >= 0; i--) {
            if (lift[i][x] != lift[i][y]) {
                x = lift[i][x];
                y = lift[i][y];
            }
        }
        return lift[0][x];
    }

    int maxEdge(int x, int y) {
        int l = lca(x, y), ans = 0;

        for (int i = log - 1; i >= 0; i--) {
            if (lvl[x] - (1 << i) >= lvl[l]) {
                ans = std::max(ans, maxe[i][x]);
                x = lift[i][x];
            }
            if (lvl[y] - (1 << i) >= lvl[l]) {
                ans = std::max(ans, maxe[i][y]);
                y = lift[i][y];
            }
        }
        return ans;
    }
};

struct HeavyLightDecomposition {
    int n, time;
    std::vector<int> sz, top, lvl, par, in, out, seq;
    std::vector<std::vector<int>> adj;

    HeavyLightDecomposition() { }
    HeavyLightDecomposition(int n) : n(n), time(0) {
        sz.resize(n);       // size of the subtree
        in.resize(n);       // in-time of dfs
        out.resize(n);      // out-time of dfs
        seq.resize(n);      // the dfs order
        lvl.resize(n);      // distance from root
        par.resize(n);      // parent of node
        top.resize(n);      // top node of HLD-thread
        adj.assign(n, {});  // adjacency matrix
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void apply(int root) {
        top[root] = root;
        dfs1(root, -1), dfs2(root);
    }

    void dfs1(int x, int p) {
        if ((par[x] = p) == -1) { lvl[x] = 0; }
        else {
            adj[x].erase(std::find(adj[x].begin(), adj[x].end(), p));
            lvl[x] = lvl[p] + 1;
        }
        sz[x] = 1;
        for (int &it : adj[x]) {
            dfs1(it, x);
            sz[x] += sz[it];
            if (sz[it] > sz[adj[x][0]]) {
                std::swap(it, adj[x][0]);
            }
        }
    }

    void dfs2(int x) {
        in[x] = time++, seq[in[x]] = x;
        for (int it : adj[x]) {
            top[it] = (it == adj[x].front()) ? top[x] : it;
            dfs2(it);
        }
        out[x] = time;
    }

    int lca(int x, int y) {
        while (top[x] != top[y]) {
            if (lvl[top[x]] > lvl[top[y]]) { x = par[top[x]]; }
            else { y = par[top[y]]; }
        }
        return (lvl[x] < lvl[y]) ? x : y;
    }

    int dist(int x, int y) {
        return lvl[x] + lvl[y] - 2 * lvl[lca(x, y)];
    }

    int jump(int x, int k) {
        if (lvl[x] < k) { return -1; }
        int depth = lvl[x] - k;
        while (lvl[top[x]] > depth) {
            x = par[top[x]];
        }
        return seq[in[x] - lvl[x] + depth];
    }
    
    // x ancestor of y ?
    bool isAncestor(int x, int y) {
        return in[x] < in[y] && in[y] < out[x];
    }
    
    // tree rooted at r
    int rootedParent(int r, int x) {
        if (r == x) { return x; }
        if (!isAncestor(x, r)) {
            return par[x];
        }
        auto itr = std::upper_bound(adj[r].begin(), adj[r].end(), x, [&] (int a, int b) {
            return in[a] < in[b];
        });
        return *(--itr);
    }

    int rootedSize(int r, int x) {
        if (r == x) { return n; }
        if (!isAncestor(x, r)) {
            return sz[x];
        }
        return n - sz[rootedParent(r, x)];
    }

    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};
