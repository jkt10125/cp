#include <vector>
#include <memory>

struct node {
    int val;
    std::shared_ptr<node> left, right;
    node(int val, std::shared_ptr<node> left, std::shared_ptr<node> right) : val(val), left(left), right(right) { }
};

using node_ptr = std::shared_ptr<node>;

std::vector<int> init;

node_ptr build(int l, int r) {
    if (l == r) return std::make_shared<node>(node{init[l], nullptr, nullptr});
    int m = (l + r) / 2;
    return std::make_shared<node>(node{0, build(l, m), build(m + 1, r)});
}

node_ptr update(int idx, int val, const node_ptr &n, int l, int r) {
    if (l == r) return std::make_shared<node>(node{val, nullptr, nullptr});
    int m = (l + r) / 2;
    auto newNode = std::make_shared<node>(n);
    if (m < idx) newNode->right = update(idx, val, n->right, m + 1, r);
    else newNode->left = update(idx, val, n->left, l, m);
    return newNode;
}

int query(int idx, const node_ptr &n, int l, int r) {
    if (l == r) return n->val;
    int m = (l + r) / 2;
    if (m < idx) return query(idx, n->right, m + 1, r);
    return query(idx, n->left, l, m);
}
