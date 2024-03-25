#include <vector>
#include <algorithm>

std::vector<int> spf, prime;

// O(n) sieve
void sieve(int n) {
    spf.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (!spf[i]) { spf[i] = i, prime.push_back(i); }
        for (int p : prime) { 
            if (p > spf[i] || i * p > n) break; 
            spf[i * p] = p; 
        }
    }
}

// prime must contain primes atleast upto sqrt(n)
bool isPrime (int n) {
    if (n < (int) spf.size()) { return (spf[n] == n); }
    for(int i : prime) { 
        if (i * i > n) break; 
        if (n % i == 0) return false; 
    } 
    return true;
}

// prime must contain primes atleast upto sqrt(n)
std::vector<int> factor(int n, bool distinct = false) {
    std::vector<int> factr;
    if (n < (int) spf.size()) {
        while (n > 1) {
            factr.push_back(spf[n]);
            n /= spf[n];
        }
    }
    else {
        for (int i : prime) {
            if (i * i > n) break;
            while (n % i == 0) { factr.push_back(i); n /= i; }
        }
        if (n > 1) factr.push_back(n);
    }
    if (distinct) {
        factr.erase(std::unique(factr.begin(), factr.end()), factr.end());
    }
    return factr;
}