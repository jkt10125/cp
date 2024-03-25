// g++ -std=c++17 -Wall -Wextra -Wno-unused-result -Wno-char-subscripts -Wshadow -Wfloat-equal -Wconversion -Wformat-signedness -Wvla -Wduplicated-cond -Wlogical-op -Wredundant-decls -ggdb3 -DDEBUG -fsanitize=undefined,address,float-divide-by-zero,float-cast-overflow -fno-omit-frame-pointer -fno-optimize-sibling-calls -fstack-protector-all -fno-sanitize-recover=all
#pragma GCC optimize("O2")

#include <bits/stdc++.h>

#define _GLIBCXX_DEBUG
#define _GLIBCXX_DEBUG_PEDANTIC
#define _FORTIFY_SOURCE 2

void __print(const int &x)                { std::cerr << x; }
void __print(const long &x)               { std::cerr << x; }
void __print(const long long &x)          { std::cerr << x; }
void __print(const unsigned &x)           { std::cerr << x; }
void __print(const unsigned long &x)      { std::cerr << x; }
void __print(const unsigned long long &x) { std::cerr << x; }
void __print(const float &x)              { std::cerr << x; }
void __print(const double &x)             { std::cerr << x; }
void __print(const long double &x)        { std::cerr << x; }
void __print(const char &x)         { std::cerr << '\'' << x << '\''; }
void __print(const char *x)         { std::cerr << '\"' << x << '\"'; }
void __print(const std::string &x)  { std::cerr << '\"' << x << '\"'; }
void __print(const bool &x)    { std::cerr << (x ? "true" : "false"); }

template <typename T> void __print(const T &);
template <typename T, typename V> void __print(const std::pair<T, V> &);

template<typename T, typename V>
void __print(const std::pair<T, V> &x) { std::cerr << '{'; __print(x.first); std::cerr << ", "; __print(x.second); std::cerr << '}'; }

template<typename T>
void __print(const T &x) { int f = 0; std::cerr << '{'; for (const auto &i: x) std::cerr << (f++ ? ", " : ""), __print(i); std::cerr << "}"; }

void _print() { std::cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) std::cerr << ", "; _print(v...); }

#define dbg(x...) std::cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #x << "] = ["; _print(x); std::cerr << "\e[39m" << std::endl;
#define ttl(x)    std::cerr << "\e[91m" << "\n\nTotal Time Measured: " << (long double) (x).count() * 1e-9 << " sec." << "\e[39m" << std::endl;
