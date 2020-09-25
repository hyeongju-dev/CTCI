#include <vector>
#include "tree.hpp"
#include "treetestutils.hpp"
#include "treenodeiterator.hpp"
using namespace std;

/* Condition: tree nodes contain links to their parents. */
template <typename T>
int getDepth(const Tree<T, true> &tree, NodePtr<T, true> node) {
    size_t depth = 0;
    if (node) {
        while (node->getParent()) {
            node = node->getParent();
            ++depth;
        }
    }
    // Check if the node is in this tree
    if (node != tree.getRoot())
        depth =  -1;
    return depth;
}

template <typename T>
NodePtr<T, true> findCommonAncestor(const Tree<T, true> &tree, NodePtr<T, true> one, NodePtr<T, true> two) {
    if (one == two)
        return one;

    auto depthL = getDepth(tree, one);
    auto depthR = getDepth(tree, two);
    if (depthL == -1 || depthR == -1)
        return nullptr;

    if (depthL > depthR) {
        swap(depthL, depthR);
        swap(one, two); // that is why we pass 'one' and 'two' arguments by values
    }

    while (depthR != depthL) {
        two = two->getParent();
        --depthR;
    }
    while (one != two) {
        one = one->getParent();
        two = two->getParent();
    }
    return one;
}

int main() {
    auto tree = TestUtils::treeFromArray<int, true>({10, 1, 12, 3, 14, 25, 16, 27, 18, 29, 10, 13, 2, 15, 4, 5, 17, 7, 19, 9});
    TestUtils::printTree(tree);

    for (auto one : tree) {
        if (one == tree.getRoot())
            continue; // it is not interesting
        for (auto two : tree) {
            if (two == tree.getRoot() || two == one)
                continue; // it is not interesting
            auto ancestor = findCommonAncestor<int>(tree, one, two);
            cout << one->getValue() << ", " << two->getValue() << " <-- ";
            cout << (ancestor ? to_string(ancestor->getValue()) : "NOT FOUND") << endl;
        }
    }
}


/* Condition: tree nodes does not contain links to their parents */
enum FindResult {
    NotFound,   // node not found in subtree
    FoundLeft,  // node found in left subtree
    FoundRight, // node found in right subtree
    FoundEqual  // node is subtree root
};

template <typename T>
FindResult findNodeFrom(const NodePtr<T> &startNode, const NodePtr<T> &node) {
    if (!startNode)
        return NotFound;
    if (startNode == node)
        return FoundEqual;
    if (findNodeFrom<T>(startNode->getLeft(), node) != NotFound)
        return FoundLeft;
    else if (findNodeFrom<T>(startNode->getRight(), node) != NotFound)
        return FoundRight;
    return NotFound;
}

template <typename T>
NodePtr<T> findCommonAncestor(const Tree<T> &tree, const NodePtr<T> &one, const NodePtr<T> &two) {
    if (one == two)
        return one;

    auto startNode = tree.getRoot();

    auto firstResult = findNodeFrom<T>(startNode, one);
    if (firstResult == NotFound)
        return nullptr;
    auto secondResult = findNodeFrom<T>(startNode, two);
    if (secondResult == NotFound)
        return nullptr;

    while (firstResult == secondResult) {
        startNode = (firstResult == FoundLeft) ? startNode->getLeft() : startNode->getRight();
        firstResult = findNodeFrom<T>(startNode, one);
        secondResult = findNodeFrom<T>(startNode, two);
    }
    return startNode;
}

int main() {
    auto tree = TestUtils::treeFromArray({10, 1, 12, 3, 14, 25, 16, 27, 18, 29, 10, 13, 2, 15, 4, 5, 17, 7, 19, 9});
    TestUtils::printTree(tree);

    for (auto one : tree) {
        if (one == tree.getRoot())
            continue; // it is not interesting
        for (auto two : tree) {
            if (two == tree.getRoot() || two == one)
                continue; // it is not interesting
            auto ancestor = findCommonAncestor<int>(tree, one, two);
            cout << one->getValue() << ", " << two->getValue() << " <-- ";
            cout << (ancestor ? to_string(ancestor->getValue()) : "NOT FOUND") << endl;
        }
    }

    // Test nodes of different trees
    auto tree2 = TestUtils::getSampleTree<int>(7);
    auto node1 = tree.getRoot()->getLeft()->getRight();
    auto node2 = tree2.getRoot()->getRight()->getLeft();
    auto ancestor = findCommonAncestor<int>(tree, node1, node2);
    cout << "Nodes below are of diffent trees: " << endl;
    cout << node1->getValue() << ", " << node2->getValue() << " <-- ";
    cout << (ancestor ? to_string(ancestor->getValue()) : "NOT FOUND") << endl;
}
