#include <vector>
#include <array>
#include <queue>

namespace FlowNetwork {
    const int INF = 1000000007;
    
    struct MinCostMaxFlow {
        
        struct Edge {
            int from, to, cap, flow, cost;
        };
        
        int n, s, t;
        std::vector<std::vector<int>> adj;
        std::vector<Edge> edges;
        std::vector<int> dist, par, par_edge;
        std::vector<bool> in_queue;

        MinCostMaxFlow(int n, int s, int t) :
            n(n), s(s), t(t),
            adj(n), dist(n), par(n),
            par_edge(n), in_queue(n) {
        }

        void addEdge(int from, int to, int cap, int cost, bool directed = true) {
            adj[from].push_back((int) edges.size());
            edges.push_back({from, to, cap, 0, cost});
            adj[to].push_back((int) edges.size());
            if (directed) {
                edges.push_back({to, from, 0, 0, -cost});
            }
            else {
                edges.push_back({to, from, cap, 0, cost});
            }
        }

        bool spfa() {
            std::fill(dist.begin(), dist.end(), INF);
            std::fill(par.begin(), par.end(), -1);
            std::fill(par_edge.begin(), par_edge.end(), -1);
            std::fill(in_queue.begin(), in_queue.end(), false);
            std::queue<int> q;
            q.push(s);
            dist[s] = 0;
            in_queue[s] = true;
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                in_queue[x] = false;
                for (int id : adj[x]) {
                    auto &e = edges[id];
                    if (e.flow < e.cap && dist[e.to] > dist[e.from] + e.cost) {
                        dist[e.to] = dist[e.from] + e.cost;
                        par[e.to] = e.from;
                        par_edge[e.to] = id;
                        if (!in_queue[e.to]) {
                            q.push(e.to);
                            in_queue[e.to] = true;
                        }
                    }
                }
            }
            return dist[t] != INF;
        }

        // returns {flow, cost}
        std::array<long long, 2> minCostMaxFlow() {
            long long flow = 0, cost = 0;
            while (spfa()) {
                int x = t, add = INF;
                while (x != s) {
                    auto &e = edges[par_edge[x]];
                    add = std::min(add, e.cap - e.flow);
                    x = par[x];
                }
                x = t;
                while (x != s) {
                    edges[par_edge[x]].flow += add;
                    edges[par_edge[x] ^ 1].flow -= add;
                    x = par[x];
                }
                flow += add;
                cost += add * 1ll * dist[t];
            }
            return {flow, cost};
        }

        std::vector<std::array<int, 2>> minCut() {
            std::vector<bool> vis(n, false);
            std::queue<int> q;
            q.push(s);
            vis[s] = true;
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (int id : adj[x]) {
                    auto &e = edges[id];
                    if (e.flow < e.cap && !vis[e.to]) {
                        vis[e.to] = true;
                        q.push(e.to);
                    }
                }
            }
            std::vector<std::array<int, 2>> res;
            for (int u = 0; u < n; u++) {
                if (!vis[u]) continue;
                for (int id : adj[u]) {
                    auto &e = edges[id];
                    if (!vis[e.to]) {
                        res.push_back({u, e.to});
                    }
                }
            }
            return res;
        }
    };
}

// Hopcroft-Karp algorithm for maximum bipartite matching
// Time Complexity: O(E sqrt(V))
// returns a vector of pairs (x, y) where x is in [0, n) and y is in [0, m)
std::vector<std::array<int, 2>> hopcroftKarp(int n, int m, const std::vector<std::array<int, 2>> &edges) {
    std::vector<int> G(edges.size()), L(n, -1), R(m, -1);
    std::vector<int> deg(n + 1), a, p, q(n);
    for (auto &[x, y] : edges) { deg[x]++; }
    for (int i = 1; i <= n; i++) { deg[i] += deg[i - 1]; }
    for (auto &[x, y] : edges) { G[--deg[x]] = y; }
    while (true) {
        a.assign(n, -1), p.assign(n, -1);
        int t = 0;
        for (int i = 0; i < n; i++) {
            if (L[i] == -1) {
                q[t++] = a[i] = p[i] = i;
            }
        }
        bool match = false;
        for (int i = 0; i < t; i++) {
            int x = q[i];
            if (L[a[x]] != -1) {
                continue;
            }
            for (int j = deg[x]; j < deg[x + 1]; j++) {
                int y = G[j];
                if (R[y] == -1) {
                    while (y != -1) {
                        R[y] = x;
                        std::swap(L[x], y);
                        x = p[x];
                    }
                    match = true;
                    break;
                }
                if (p[R[y]] == -1) {
                    q[t++] = y = R[y];
                    p[y] = x;
                    a[y] = a[x];
                }
            }
        }
        if (!match) {
            break;
        }
    }
    std::vector<std::array<int, 2>> res;
    for (int i = 0; i < n; i++) {
        if (L[i] != -1) {
            res.push_back({i, L[i]});
        }
    }
    return res;
}