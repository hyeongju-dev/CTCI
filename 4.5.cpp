#include <vector>
#include "tree.hpp"
#include "treetestutils.hpp"
using namespace std;

template <typename T>
bool checkNode(const NodePtr<T> &node, const T *minValue, const T *maxValue) {
    if (!node)
        return true;
    if (minValue && node->getValue() <= *minValue)
        return false;
    if (maxValue && node->getValue() > *maxValue)
        return false;

    return checkNode<T>(node->getLeft(), minValue, &node->getValue()) && checkNode<T>(node->getRight(), &node->getValue(), maxValue);
}

template <typename T>
bool isValidBST(const Tree<T> &tree) {
    return checkNode<T>(tree.getRoot(), nullptr, nullptr);
}

int main() {
    // valid BST
    auto tree = TestUtils::getSampleTree<int>(20);
    TestUtils::printTree(tree);
    cout << "The tree is " << (isValidBST<int>(tree) ? "" : "NOT ") << "binary search tree" << endl;

    // invalid BST
    tree.getRoot()->getRight()->getRight()->getRight()->setLeftChild(make_shared<Node<int>>(19));
    TestUtils::printTree(tree);
    cout << "The tree is " << (isValidBST<int>(tree) ? "" : "NOT ") << "binary search tree" << endl;

    // invalid BST
    tree.getRoot()->getRight()->getRight()->getRight()->setLeftChild(make_shared<Node<int>>(15));
    TestUtils::printTree(tree);
    cout << "The tree is " << (isValidBST<int>(tree) ? "" : "NOT ") << "binary search tree" << endl;
}
