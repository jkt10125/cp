// #include <cstdio>
#include <string>
// #include <type_traits>

template <typename T, std::enable_if_t<std::is_same_v<T, char>, int> = 0>
char in() { return getchar_unlocked(); }

template <class T, std::enable_if_t<std::is_integral_v<T> and not std::is_same_v<T, char>, int> = 0>
T in() {
    char c; do { c = getchar_unlocked(); } while (isspace(c));
    if (std::is_signed<T>::value and c == '-') return -in<T>();
    T n = 0;
    do { n = n * 10 + c - '0'; } while (not isspace(c = getchar_unlocked()));
    return n;
}

template <typename T, std::enable_if_t<std::is_same_v<T, std::string>, int> = 0>
std::string in() {
    char c; do { c = getchar_unlocked(); } while (isspace(c));
    std::string s;
    do { s.push_back(c); } while (not isspace(c = getchar_unlocked()));
    return s;
}

void out(char c) { putchar_unlocked(c); }

void out(const std::string &s) { for (char c : s) putchar_unlocked(c); }

void out(int n) {
    if (n < 0) { putchar_unlocked('-'); n = -n; }
    char s[20];
    int i = 0;
    do { s[i++] = n % 10; n /= 10; } while (n);
    while (i) putchar_unlocked(s[--i] + '0');
}

int main() {
    int a = in<int>();
    std::string s = in<std::string>();
    char c = in<char>();

    out(a);
    out(' ');
    out(s);
    out(' ');
    out(c);
    out('\n');
    return 0;
}