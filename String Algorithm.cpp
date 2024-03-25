#include <vector>
#include <string>

std::vector<int> prefixFunction (const std::string &s) {
    int n = (int) s.size();
    std::vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) { j = pi[j - 1]; }
        if (s[i] == s[j]) { j++; } pi[i] = j;
    }
    return pi;
}

std::vector<int> manacher(const std::string &s) {
    std::string t = "#";
    int n = (int) (s.size() << 1 | 1);
    for (auto c : s) {
        t += (std::string(1, c) + "#");
    }
    std::vector<int> r(n);
    for (int i = 0, j = 0; i < n; i++) {   
        if ((j << 1) - i >= 0 && j + r[j] > i) {
            r[i] = std::min(r[(j << 1) - i], j + r[j] - i);
        }
        while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]]) {
            r[i]++;
        }
        if (i + r[i] > j + r[j]) {
            j = i;
        }
    }
    return r;
}