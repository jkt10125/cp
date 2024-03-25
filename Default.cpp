#include <bits/stdc++.h>

void __print(const int &x) { std::cerr << x; }
void __print(const long &x) { std::cerr << x; }
void __print(const long long &x) { std::cerr << x; }
void __print(const unsigned &x) { std::cerr << x; }
void __print(const unsigned long &x) { std::cerr << x; }
void __print(const unsigned long long &x) { std::cerr << x; }
void __print(const float &x) { std::cerr << x; }
void __print(const double &x) { std::cerr << x; }
void __print(const long double &x) { std::cerr << x; }
void __print(const char &x) { std::cerr << '\'' << x << '\''; }
void __print(const char *x) { std::cerr << '\"' << x << '\"'; }
void __print(const std::string &x) { std::cerr << '\"' << x << '\"'; }
void __print(const bool &x) { std::cerr << (x ? "true" : "false"); }

template <typename T> void __print(const T &);
template <typename T, typename V> void __print(const std::pair<T, V> &);

template<typename T, typename V>
void __print(const std::pair<T, V> &x) { std::cerr << '{'; __print(x.first); std::cerr << ", "; __print(x.second); std::cerr << '}'; }

template<typename T>
void __print(const T &x) { int f = 0; std::cerr << '{'; for (const auto &i: x) std::cerr << (f++ ? ", " : ""), __print(i); std::cerr << '}'; }

void _print() { std::cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) std::cerr << ", "; _print(v...); }

#define dbg(x...) std::cerr << __func__ << ":" << __LINE__ << " [" << #x << "] = ["; _print(x); std::cerr << std::endl;

// safe_xxx(a, b, res);
// these functions return true if overflow is occurred
#define safe_mul __builtin_mul_overflow
#define safe_sub __builtin_sub_overflow
#define safe_add __builtin_add_overflow

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &x : v) { is >> x; }
    return is;
}

template <typename T, const size_t n>
std::istream &operator>>(std::istream &is, std::array<T, n> &v) {
    for (auto &x : v) { is >> x; }
    return is;
}

using namespace std;

void solve() {
    
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    std::cin >> T;
    for (int testcase = 1; testcase <= T; testcase++) {
        solve();
    }
    return 0;
}

#ifdef COMMENT
Author: leaf_node(jkt)

Some advice while solving problems:
1. Read the problem statement carefully (most of the times, you will find the answer there itself)
2. Keep eye on the constraints (it will help you to guess the complexity of the solution)
3. Analyzse the sample test cases carefully and try to find the pattern
4. Think of some edge cases and try to solve them manually
5. Always check for overflow before submitting the code.
5. Donot spend too much time on a single method (if the approach is not clear, try to think of some other approach)
6. Always be organised while coding (it will help you to debug the code easily)
7. Its always better to think 5 mins before submitting the code rather than getting WA and then thinking for 30 mins.
8. WA for pretest 2 is not your enemy! the real enemy is the person who shook the jar. XD
#endif

