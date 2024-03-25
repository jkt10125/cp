#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template <typename T, class cmp = std::less<T>>
using ordered_set = tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

// Ordered Set from Policy Based Data Structures (PBDS)
// Supports:
// 1. find_by_order(k): returns iterator to kth element (0-indexed)
// 2. order_of_key(k): returns number of elements strictly less than k