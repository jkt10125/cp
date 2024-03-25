#include <vector>
#include <array>

struct DisjointSetUnion {
private:
    std::vector<int> arr;
    std::vector<std::array<int, 2>> m_history;

public:
    DisjointSetUnion(int n) : arr(n, -1) { }

    int find(int x) {
        return arr[x] < 0 ? x : arr[x] = find(arr[x]);
    }

    int time() {
        return (int) m_history.size();
    }

    void rollBack(int t) {
        for (int i = (int) m_history.size() - 1; i >= t; --i) {
            arr[m_history[i][0]] = m_history[i][1];
        }
        m_history.resize(t, {});
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (arr[x] > arr[y]) {
            std::swap(x, y);
        }
        m_history.push_back({x, arr[x]});
        m_history.push_back({y, arr[y]});
        arr[x] += arr[y];
        arr[y] = x;
        return true;
    }

    int size(int x) {
        return -arr[find(x)];
    }

    void clear() {
        arr.assign(arr.size(), -1);
    }
};