#include <vector>
#include <functional>


std::vector<int> articulationPoints(const std::vector<std::vector<int>> &A) {
    int n = (int) A.size(), time = 0;
    std::vector<int> low(n, -1), tin(n, -1), vis(n, false), art_points;
    std::function<void(int, int)> dfs = [&] (int x, int p) {
        vis[x] = true; low[x] = tin[x] = time++;
        int child = 0; bool ok = false;
        for (int y : A[x]) {
            if (y == p) { continue; }
            if (vis[y]) { low[x] = std::min(low[x], tin[y]); }
            else {
                dfs(y, x);
                low[x] = std::min(low[x], low[y]);
                if (low[y] >= tin[x] && p != -1) { ok = true; }
                child++;
            }
        }
        if (p == -1 && child > 1) { ok = true; }
        if (ok) { art_points.push_back(x); }
    };
    for (int i = 0; i < n; i++) { if (!vis[i]) { dfs(i, -1); } }
    return art_points;
}

std::vector<std::array<int, 2>> bridges(const std::vector<std::vector<int>> &A) {
    int n = (int) A.size(), time = 0;
    std::vector<int> low(n, -1), tin(n, -1), vis(n, false);
    std::vector<std::array<int, 2>> bridges;
    std::function<void(int, int)> dfs = [&] (int x, int p) {
        vis[x] = true; low[x] = tin[x] = time++;
        for (int y : A[x]) {
            if (y == p) {
                continue;
            }
            if (vis[y]) {
                low[x] = std::min(low[x], tin[y]);
            }
            else {
                dfs(y, x);
                low[x] = std::min(low[x], low[y]);
                if (low[y] > tin[x]) {
                    bridges.push_back({x, y});
                }
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, -1);
        }
    }
    return bridges;
};

std::vector<int> topo_sort(const std::vector<std::vector<int>> &A) {
    int n = A.size();
    std::vector<int> order, vis(n, false);
    std::function<void(int)> dfs = [&] (int x) {
        vis[x] = true;
        for (int y : A[x]) {
            if (!vis[y]) {
                dfs(y);
            }
        }
        order.push_back(x);
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    return std::reverse(order.begin(), order.end()), order;
}

namespace StronglyConnectedComponents {
    // KosaRaju's Algorithm
    std::vector<std::vector<int>> get_scc(const std::vector<std::vector<int>> &A) {
        int n = A.size();
        std::vector<std::vector<int>> rA(n), SCC;
        for (int i = 0; i < n; i++) {
            for (int j : A[i]) {
                rA[j].push_back(i);
            }
        }
        std::vector<bool> vis(n, false);
        std::function<void(int)> scc_dfs = [&] (int x) {
            vis[x] = true;
            SCC.back().push_back(x);
            for (int y : rA[x]) {
                if (!vis[y]) {
                    scc_dfs(y);
                }
            }
        };
        for (int x : topo_sort(A)) {
            if (!vis[x]) {
                SCC.emplace_back();
                scc_dfs(x);
            }
        }
        return SCC;
    }

    std::vector<int> get_ids(const std::vector<std::vector<int>> &SCC) {
        int m = SCC.size(), max = -1;
        for (const std::vector<int> &scc_i : SCC) {
            max = std::max(max, *std::max_element(scc_i.begin(), scc_i.end()));
        }
        std::vector<int> id(max + 1);
        for (int i = 0; i < m; i++) {
            for (const int &it : SCC[i]) {
                id[it] = i;
            }
        }
        return id;
    }

    std::vector<std::vector<int>> make_condensed_graph(const std::vector<std::vector<int>> &A, const std::vector<int> &id) {
        std::vector<std::vector<int>> G(*std::max_element(id.begin(), id.end()) + 1);
        int n = A.size();
        for (int i = 0; i < n; i++) {
            for (const int &j : A[i]) {
                if (id[i] != id[j]) {
                    G[id[i]].push_back(id[j]);
                }
            }
        }
        return G;
    }
}