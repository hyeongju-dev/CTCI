#include <deque>
#include <list>
#include <cassert>
#include "tree.hpp"
#include "treetestutils.hpp"
using namespace std;

template <typename T>
list<deque<T>> possibleStableJoins(deque<T> &prefix, deque<T> &left, deque<T> &right);

template <typename T>
list<deque<T>> possibleArrays(const NodePtr<T> &root) {
    list<deque<T>> result;
    if (!root) {
        result.emplace_back(); // empty is required to call cycle body at least once
        return result;
    }

    auto leftArrays = possibleArrays<T>(root->getLeft());
    auto rightArrays = possibleArrays<T>(root->getRight());

    deque<T> prefix;
    prefix.push_back(root->getValue());
    for (auto &left : leftArrays)
        for (auto &right : rightArrays) {
            auto joins = possibleStableJoins<T>(prefix, left, right);
            result.splice(result.end(), move(joins));
            assert(prefix.size() == 1 && prefix[0] == root->getValue());
        }
    return result;
}

template <typename T>
list<deque<T>> possibleStableJoins(deque<T> &prefix, deque<T> &left, deque<T> &right) {
    list<deque<T>> result;

    if (left.empty() || right.empty()) {
        deque<T> r(prefix);
        r.insert(r.end(), left.begin(), left.end());
        r.insert(r.end(), right.begin(), right.end());
        result.push_back(move(r));
        return result;
    }

    prefix.push_back(left.front());
    left.pop_front();
    result.splice(result.end(), possibleStableJoins(prefix, left, right));
    left.push_front(prefix.back());
    prefix.pop_back();

    prefix.push_back(right.front());
    right.pop_front();
    result.splice(result.end(), possibleStableJoins(prefix, left, right));
    right.push_front(prefix.back());
    prefix.pop_back();

    return result;
}

int main() {
    auto tree = TestUtils::treeFromArray({5, 10, 15, 20, 25, 50, 60, 65, 70, 80});
    TestUtils::printTree(tree);
    // auto tree = TestUtils::treeFromArray({2, 3, 1});
    auto result = possibleArrays<int>(tree.getRoot());

    for (auto &array : result) {
        string sep;
        cout << "{";
        for (auto &n : array) {
            cout << sep << n;
            if (sep.empty())
                sep = ", ";
        }
        cout << "}" << endl;
    }
}
