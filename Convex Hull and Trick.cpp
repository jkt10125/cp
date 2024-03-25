#include <vector>
#include <algorithm>
#include <set>
#include <cassert>
#include <climits>

struct point {
    int x, y;
    point() = default;
    point(int t_x, int t_y) : x(t_x), y(t_y) {}
    point operator-(const point &p) const {
        return point(x - p.x, y - p.y); 
    }
    long long cross(const point &p) const {
        return x * 1ll * p.y - y * 1ll * p.x;
    }
    long long cross(const point &a, const point &b) const {
        return (a - *this).cross(b - *this);
    }
    bool operator==(const point &p) const {
        return (x == p.x) && (y == p.y);
    }
    bool operator<(const point &p) const {
        return (x == p.x) ? (y < p.y) : (x < p.x);
    }
};

std::vector<point> convexHull(std::vector<point> pts) {
    if (pts.size() <= 1) return pts;
    std::sort(pts.begin(), pts.end());
    std::vector<point> H(pts.size() + 1);
    int s = 0, t = 0;
    for (int i = 2; i--; s = --t, std::reverse(pts.begin(), pts.end())) {
        for (point &p : pts) {
            while (t > s + 1 && H[t - 2].cross(H[t - 1], p) <= 0) {
                t--;
            }
            H[t++] = p;
        }
    }
    return {H.begin(), H.begin() + t - (t == 2 && H[0] == H[1])};
}

struct line {
    mutable int m, c, p, isline;
    bool operator < (const line &L) const {
        return ((L.isline) ? (m < L.m) : (p < L.p));
    }
};

class ConvexHullTrick : std::multiset<line> {
    int mode;

    int div (int a, int b) {
        return (a / b - ((a ^ b) < 0 && a % b));
    }
    
    bool isect (iterator x, iterator y){
        if (y == end()) {
            x->p = INT_MAX;
            return false;
        }
        x->p = (x->m == y->m) ? (x->c > y->c) ? INT_MAX : INT_MIN : div ((y->c - x->c), (x->m - y->m));
        return (x->p >= y->p);
    }
    
public:
    ConvexHullTrick() : mode(1) { } // initially set to report max answer

    inline void flip_mode() { mode *= -1; }
    
    void add (int sl, int in) {
        auto z = insert({mode * sl, mode * in, 0, 1});
        auto y = z++;
        auto x = y;
        while (isect(y, z)) {
            z = erase(z);
        }
        if(x != begin() && isect(--x, y)) {
            isect(x, y = erase(y));
        }
        while((y = x) != begin() && (--x)->p >= y->p) {
            isect(x, erase(y));
        }
    }
    
    int query (int x) {
        assert (!empty());
        auto l = *lower_bound({0, 0, x, 0});
        return mode * (l.m * x + l.c);
    }
};

int main() {
    
}