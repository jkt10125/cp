#include <vector>
#include <array>

template <typename T>
struct Matrix : std::vector<std::vector<T>> {
    Matrix(int row, int col, T val) {
        this->resize(row, std::vector<T>(col, val));
    }

    static Matrix identity(int n) {
        Matrix res(n, n, T(0));
        for (int i = 0; i < n; ++i) {
            res[i][i] = T(1);
        }
        return res;
    }

    Matrix operator += (const Matrix &rhs) {
        for (int i = 0; i < this->size(); ++i) {
            for (int j = 0; j < (*this)[i].size(); ++j) {
                (*this)[i][j] += rhs[i][j];
            }
        }
        return *this;
    }

    Matrix operator + (const Matrix &rhs) const {
        return Matrix(*this) += rhs;
    }

    Matrix operator -= (const Matrix &rhs) {
        for (int i = 0; i < this->size(); ++i) {
            for (int j = 0; j < (*this)[i].size(); ++j) {
                (*this)[i][j] -= rhs[i][j];
            }
        }
        return *this;
    }

    Matrix operator - (const Matrix &rhs) const {
        return Matrix(*this) -= rhs;
    }

    Matrix operator *= (const Matrix &rhs) {
        return *this = *this * rhs;
    }

    Matrix operator * (const Matrix &rhs) const {
        Matrix res(this->size(), rhs[0].size(), T(0));
        for (int i = 0; i < res.size(); ++i) {
            for (int j = 0; j < res[i].size(); ++j) {
                for (int k = 0; k < rhs.size(); ++k) {
                    res[i][j] += (*this)[i][k] * rhs[k][j];
                }
            }
        }
        return res;
    }

    Matrix operator *= (const T &rhs) {
        for (int i = 0; i < this->size(); ++i) {
            for (int j = 0; j < (*this)[i].size(); ++j) {
                (*this)[i][j] *= rhs;
            }
        }
        return *this;
    }

    Matrix operator * (const T &rhs) const {
        return Matrix(*this) *= rhs;
    }

    Matrix operator /= (const T &rhs) {
        for (int i = 0; i < this->size(); ++i) {
            for (int j = 0; j < (*this)[i].size(); ++j) {
                (*this)[i][j] /= rhs;
            }
        }
        return *this;
    }

    Matrix operator / (const T &rhs) const {
        return Matrix(*this) /= rhs;
    }

    Matrix pow(long long k) const {
        Matrix res = identity(this->size()), x = *this;
        for (; k; k >>= 1) {
            if (k & 1) res *= x;
            x *= x;
        }
        return res;
    }

    // Matrix Transpose 
    Matrix operator ! () const {
        Matrix res(this[0].size(), this->size(), T(0));
        for (int i = 0; i < res.size(); ++i) {
            for (int j = 0; j < res[i].size(); ++j) {
                res[i][j] = (*this)[j][i];
            }
        }
        return res;
    }

    T determinant() const {
        Matrix a = *this;
        T res = T(1);
        for (int i = 0; i < a.size(); ++i) {
            int idx = -1;
            for (int j = i; j < a.size(); ++j) {
                if (a[j][i] != T(0)) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) {
                return T(0);
            }
            if (idx != i) {
                res = -res;
                for (int j = i; j < a.size(); ++j) {
                    std::swap(a[i][j], a[idx][j]);
                }
            }
            res *= a[i][i];
            T inv = T(1) / a[i][i];
            for (int j = i; j < a.size(); ++j) {
                a[i][j] *= inv;
            }
            for (int j = i + 1; j < a.size(); ++j) {
                T mul = a[j][i];
                for (int k = i; k < a.size(); ++k) {
                    a[j][k] -= a[i][k] * mul;
                }
            }
        }
        return res;
    }

    Matrix inverse() const {
        Matrix a = *this;
        std::vector<std::array<int, 2>> swaps;
        for (int i = 0; i < a.size(); ++i) {
            int idx = -1;
            for (int j = i; j < a.size(); ++j) {
                if (a[j][i] != T(0)) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) {
                return Matrix(0, 0, T(0));
            }
            if (idx != i) {
                swaps.push_back({idx, i});
                a[idx].swap(a[i]);
            }
            a[i][i] = T(1) / a[i][i];
            for (int j = 0; j < a.size(); ++j) {
                if (j == i) continue;
                a[i][j] *= a[i][i];
            }
            for (int j = 0; j < a.size(); ++j) {
                if (j == i) continue;
                for (int k = 0; k < a.size(); ++k) {
                    if (k == i) continue;
                    a[j][k] -= a[j][i] * a[i][k];
                }
                a[j][i] *= -a[i][i];
            }
        }
        for (int i = swaps.size(); i--;) {
            for (int j = 0; j < a.size(); ++j) {
                std::swap(a[j][swaps[i][0]], a[j][swaps[i][1]]);
            }
        }
        return a;
    }
};