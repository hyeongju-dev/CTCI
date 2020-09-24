#include <limits>
#include "tree.hpp"
#include "treetestutils.hpp"
using namespace std;

template <typename T>
int getHeight(const NodePtr<int> &node) {
    if (!node)
        return 0;

    int leftH = getHeight<T>(node->getLeft());
    if (leftH == -1)
        return -1;

    int rightH = getHeight<T>(node->getRight());
    if (rightH == -1)
        return -1;

    if (abs(leftH - rightH) > 1)
        return -1;
    return max(leftH, rightH) + 1;
}

template <typename T>
bool isTreeBalanced(const Tree<T> &tree) {
    return getHeight<T>(tree.getRoot()) != -1;
}

int main() {
    // Balanced tree
    auto tree = TestUtils::getSampleTree<int>(20);
    cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << endl;

    // Disconnect right subtree, the result tree is not balanced
    auto r = tree.getRoot()->getRight();
    tree.getRoot()->getRight() = make_shared<Node<int>>(100);
    cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << endl;

    // Return right subtree and check if the tree is balanced again
    tree.getRoot()->getRight() = r; // balanced
    cout << "Tree is " << (isTreeBalanced<int>(tree) ? "" : "NOT ") << "balanced" << endl;
    
    return 0;
}
