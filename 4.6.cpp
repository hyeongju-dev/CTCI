#include <vector>
#include "tree.hpp"
#include "treetestutils.hpp"
using namespace std;

template <typename T>
NodePtr<T, true> getMin(NodePtr<T, true> node) {
    if (!node)
        return nullptr;
    while (node->getLeft())
        node = node->getLeft();
    return node;
}

template <typename T>
NodePtr<T, true> nextNode(NodePtr<T, true> node) {
    if (!node)
        return nullptr;
    if (node->getRight())
        return getMin<T>(node->getRight());
    auto next = node->getParent();
    while (next && node == next->getRight()) {
        node = next;
        next = next->getParent();
    }
    return next;
}

int main() {
    // valid BST
    auto tree = TestUtils::getSampleTree<int, true>(20);
    TestUtils::printTree(tree);
    auto node = getMin<int>(tree.getRoot());
    if (node) {
        cout << node->getValue();
        for (node = nextNode<int>(node); node; node = nextNode<int>(node))
            cout << " --> " << node->getValue();
        cout << endl;
    }
}
