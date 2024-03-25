#include <vector>
#include <array>

template <const int K>
struct Trie {
    std::vector<std::array<int, K + 2>> arr;
    std::vector<int> m_del;

    Trie() : arr(1, {}) { }

    int newNode() {
        if (m_del.empty()) {
            arr.push_back({});
            return arr.size() - 1;
        }
        int idx = m_del.back();
        m_del.pop_back();
        arr[idx] = {};
        return idx;
    }

    void insert(const std::vector<int> &A) {
        int node = 0;
        arr[0][K]++;
        for (int it : A) {
            if (arr[node][it] == 0) {
                arr[node][it] = newNode();
            }
            node = arr[node][it];
            arr[node][K]++;
        }
        arr[node][K + 1]++;
    }

    int erase(const std::vector<int> &A, int idx = 0, int node = 0) {
        if (idx == (int) A.size()) {
            if (arr[node][K + 1]) {
                arr[node][K]--;
                arr[node][K + 1]--;
                return true;
            }
            return false;
        }
        if (arr[node][A[idx]] == 0) {
            return false;
        }
        int ok = erase(A, idx + 1, arr[node][A[idx]]);
        if (ok) {
            arr[node][K]--;
            if (arr[arr[node][A[idx]]][K] = 0) {
                m_del.push_back(arr[node][A[idx]]);
                arr[node][A[idx]] = 0;
            }
        }
        return ok;
    }

    // this function should be modified according to the need
    int search(const std::vector<int> &A) {
        int node = 0;
        for (int i = 0; i < (int) A.size(); i++) {
            if (!arr[node][A[i]]) {
                return 0;
            }
            node = arr[node][A[i]];
        }
        return arr[node][K + 1];
    }

    int size() {
        return arr[0][K];
    }
};

// [2]: # of integers that pass through this node
struct BitTrie : std::vector<std::array<int, 3>> {
public:
    BitTrie() {
        this->push_back({0, 0, 0});
        insert(0, 1);   // <-- Inserted 0 into the Trie
    }

    void insert(int t_x, int t_v) {
        int node = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (t_x >> i) & 1;
            if (!(*this)[node][bit]) {
                (*this)[node][bit] = (int) this->size();
                this->push_back({0, 0, 0});
            }
            node = (*this)[node][bit];
            (*this)[node][2] += t_v;
        }
    }

    int maxXor(int t_x) {
        int node = 0, ans = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (t_x >> i) & 1;
            if ((*this)[(*this)[node][bit ^ 1]][2]) {
                ans |= (1 << i);
                node = (*this)[node][bit ^ 1];
            }
            else {
                node = (*this)[node][bit];
            }
        }
        return ans;
    }

    int xorNotGtk(int t_x, int t_k) {
        int ctr = 0, node = 0;
        for (int i = 30; i >= 0; i--) {
            int x1 = (t_x >> i) & 1, k1 = (t_k >> i) & 1;
            if (k1) {
                ctr += (*this)[(*this)[node][x1 ^ 1]][2];
                node = (*this)[node][x1];
            }
            else {
                node = (*this)[node][x1];
            }
        }
        return ctr;
    }
};