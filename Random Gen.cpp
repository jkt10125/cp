#include <chrono>
#include <random>

std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

int gen(int l, int r) {
    return std::uniform_int_distribution<int>(l, r)(rng);
}

template <typename Iter>
void randomShuffle(Iter t_begin, Iter t_end) {
    std::shuffle(t_begin, t_end, rng);
}