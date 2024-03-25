#include <bits/stdc++.h>

/*-----------------------------------------------------                     ---------------------------------------------------------------------
Explicitly defined these functions because of bottom 4.                     Intentionally not returning the istream object to not allow chaining.
-------------------------------------------------------                     -------------------------------------------------------------------*/
void __print(const int &x) { std::cerr << x; }                              void __read(int &x) { std::cin >> x; }
void __print(const long &x) { std::cerr << x; }                             void __read(long &x) { std::cin >> x; }
void __print(const long long &x) { std::cerr << x; }                        void __read(long long &x) { std::cin >> x; }
void __print(const unsigned &x) { std::cerr << x; }                         void __read(unsigned &x) { std::cin >> x; }
void __print(const unsigned long &x) { std::cerr << x; }                    void __read(unsigned long &x) { std::cin >> x; }
void __print(const unsigned long long &x) { std::cerr << x; }               void __read(unsigned long long &x) { std::cin >> x; }
void __print(const float &x) { std::cerr << x; }                            void __read(float &x) { std::cin >> x; }
void __print(const double &x) { std::cerr << x; }                           void __read(double &x) { std::cin >> x; }
void __print(const long double &x) { std::cerr << x; }                      void __read(long double &x) { std::cin >> x; }
void __print(const char &x) { std::cerr << '\'' << x << '\''; }             void __read(char &x) { std::cin >> x; }
void __print(const char *x) { std::cerr << '\"' << x << '\"'; }             // void __read(char *x) { std::cin >> x; }
void __print(const std::string &x) { std::cerr << '\"' << x << '\"'; }      void __read(std::string &x) { std::cin >> x; }
void __print(const bool &x) { std::cerr << (x ? "true" : "false"); }        void __read(bool &x) { std::cin >> x; }

// Forward declaration to handle the case of pair of vectors.
template <typename T> void __print(const T &);
template <typename T, typename V> void __print(const std::pair<T, V> &);

template <typename T, typename V>
void __print(const std::pair<T, V> &x) { std::cerr << '{'; __print(x.first); std::cerr << ", "; __print(x.second); std::cerr << '}'; }

template <typename T>
void __print(const T &x) { int f = 0; std::cerr << '{'; for (const auto &i: x) std::cerr << (f++ ? ", " : ""), __print(i); std::cerr << '}'; }

void _print() { std::cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) std::cerr << ", "; _print(v...); }

// We are forced to use this macro because of the value of __func__ and __LINE__.
#define dbg(x...) std::cerr << __func__ << ":" << __LINE__ << " [" << #x << "] = ["; _print(x); std::cerr << std::endl;

// Forward declaration to handle the case of pair of vectors.
template <typename T> void __read(T &);
template <typename T, typename V> void __read(std::pair<T, V> &);

template <typename T, typename V>
void __read(std::pair<T, V> &x) { __read(x.first); __read(x.second); }

template <typename T>
void __read(T &x) { for (auto &i : x) { __read(i); } }

template <class T, class... U>
void re(T&& a, U&&... b) { __read(std::forward<T>(a)); (void)std::initializer_list<int>{(__read(std::forward<U>(b)), 0)...}; }

#define SUPPRESS_WARNINGS(x) (void)(x)

void setIO(std::string input = "", std::string output = "") {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    if (!input.empty()) { freopen(input.c_str(), "r", stdin); }
    if (!output.empty()) { freopen(output.c_str(), "w", stdout); }
}

using namespace std;

void precompute() {
    
}

void solve(int _) {
    SUPPRESS_WARNINGS(_);
    
}

signed main() {
    setIO();
    precompute();
    int t = 1;
    std::cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve(_);
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