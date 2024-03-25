#include <array>

template <const int BASE, const int LEN>
struct ArbitraryBaseInt : std::array<int, LEN> {
    ArbitraryBaseInt() { }

    ArbitraryBaseInt &operator += (const ArbitraryBaseInt &rhs) {
        for (int i = 0, c = 0; i < LEN; i++) {
            (*this)[i] += c + rhs[i];
            c = ((*this)[i] < BASE) ? 0 : ((*this)[i] -= BASE, 1);
        }
        return (*this);
    }

    ArbitraryBaseInt operator + (const ArbitraryBaseInt &rhs) const {
        return ArbitraryBaseInt(*this) += rhs;
    }

    ArbitraryBaseInt &operator -= (const ArbitraryBaseInt &rhs) {
        for (int i = 0, c = 0; i < LEN; i++) {
            (*this)[i] -= c + rhs[i];
            c = ((*this)[i] < 0) ? ((*this)[i] += BASE, 1) : 0;
        }
        return (*this);
    }

    ArbitraryBaseInt operator - (const ArbitraryBaseInt &rhs) const {
        return ArbitraryBaseInt(*this) -= rhs;
    }

    /* Assumption: res < BASE */
    ArbitraryBaseInt &operator += (const int &rhs) {
        for (int i = 0, c = rhs; i < LEN && c; i++) {
            (*this)[i] += c;
            c = ((*this)[i] < BASE) ? 0 : ((*this)[i] -= BASE, 1);
        }
        return (*this);
    }

    ArbitraryBaseInt operator + (const int &rhs) const {
        return ArbitraryBaseInt(*this) += rhs;
    }

    ArbitraryBaseInt &operator -= (const int &rhs) {
        for (int i = 0, c = rhs; i < LEN && c; i++) {
            (*this)[i] -= c;
            c = ((*this)[i] < 0) ? ((*this)[i] += BASE, 1) : 0;
        }
        return (*this);
    }

    ArbitraryBaseInt operator - (const int &rhs) const {
        return ArbitraryBaseInt(*this) -= rhs;
    }

    ArbitraryBaseInt &operator *= (const int &rhs) {
        for (int i = 0, c = 0; i < LEN; i++) {
            (*this)[i] = (*this)[i] * rhs + c;
            (c = (*this)[i] / BASE) ? (*this)[i] -= c * BASE : 0;
        }
        return (*this);
    }

    ArbitraryBaseInt operator * (const int &rhs) const {
        return ArbitraryBaseInt(*this) *= rhs;
    }

    ArbitraryBaseInt &operator /= (const int &rhs) {
        for (int i = LEN - 1, c = 0; i >= 0; i--) {
            (*this)[i] += c * BASE;
            c = (*this)[i] % rhs;
            (*this)[i] /= rhs;
        }
        return (*this);
    }

    ArbitraryBaseInt operator / (const int &rhs) const {
        return ArbitraryBaseInt(*this) /= rhs;
    }
};

int main() {
    
}