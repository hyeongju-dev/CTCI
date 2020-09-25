#include "tree.hpp"
#include "treenodeiterator.hpp"
#include "treetestutils.hpp"
using namespace std;

/* Recursive solution with Tree traversing */
template <typename T>
bool compareTrees(const NodePtr<T> &left, const NodePtr<T> &right);

template <typename T>
bool checkSubtree(const NodePtr<T> &root, const NodePtr<T> &subtreeRoot);

template <typename T>
bool checkSubtree(const Tree<T> &tree, const Tree<T> &subtree) {
    if (!subtree.getRoot())
        return true; // empty subtree
    return checkSubtree<T>(tree.getRoot(), subtree.getRoot());
}

template <typename T>
bool compareTrees(const NodePtr<T> &left, const NodePtr<T> &right) {
    if (!left && !right)
        return true;
    else if (!left || !right) // one tree is not finished, another already finished
        return false;
    else if (left->getValue() == right->getValue())
        return compareTrees<T>(left->getLeft(), right->getLeft()) && compareTrees<T>(left->getRight(), right->getRight());
    return false;
}

template <typename T>
bool checkSubtree(const NodePtr<T> &root, const NodePtr<T> &subtreeRoot) {
    if (!root)
        return false;
    if (root->getValue() == subtreeRoot->getValue() && compareTrees<T>(root, subtreeRoot))
        return true;
    return checkSubtree<T>(root->getLeft(), subtreeRoot) || checkSubtree<T>(root->getRight(), subtreeRoot);
}

int main() {
    auto left = TestUtils::getSampleTree<int>(15);
    auto right = TestUtils::getSampleTree<int>(7);
    TestUtils::printTree(right);
    cout << (checkSubtree<int>(left, right) ? "is subtree of\n" : "is not subtree of\n");
    TestUtils::printTree(left);

    cout << endl;
    right = TestUtils::getSampleTree<int>(8);
    TestUtils::printTree(right);
    cout << (checkSubtree<int>(left, right) ? "is subtree of\n" : "is not subtree of\n");
    TestUtils::printTree(left);
}
