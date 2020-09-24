/* treenode.hpp */
#pragma once
#include <memory>
using namespace std;

template <typename Node, bool WithParent>
class NodeBase {
public:
    NodeBase() = default;
    NodeBase(const shared_ptr<Node> &p) : parent(p) {}

    shared_ptr<Node> getParent() { return parent.lock(); }
private:
    weak_ptr<Node> parent;
};

// Specialization for tree node containing no reference to parent
template <typename Node>
class NodeBase<Node, false> {
public:
    NodeBase() = default;
    NodeBase(const shared_ptr<Node> &) {}

private:
};

template <typename T, bool WithParent = false>
class Node : public NodeBase<Node<T, WithParent>, WithParent> {
    using Super = NodeBase<Node, WithParent>;

public:
    using NodePtr = shared_ptr<Node>;

    Node(T &&v) : value(move(v)) {}
    Node(const T &v) : value(v) {}
    Node(T &&v, const NodePtr &parent) : Super(parent), value(move(v)) {}
    Node(const T &v, const NodePtr &parent) : Super(parent), value(v) {}

    const T &getValue() const { return value; }

    const NodePtr &getLeft() const { return childs.first; }
    NodePtr &getLeft() { return childs.first; }

    const NodePtr &getRight() const { return childs.second; }
    NodePtr &getRight() { return childs.second; }

    template <typename U>
    void setLeftChild(U &&node) { childs.first = forward<U>(node); }

    template <typename U>
    void setRightChild(U &&node) { childs.second = forward<U>(node); }

protected:
    T value;
    pair<NodePtr, NodePtr> childs;
};


/* tree.hpp */
#pragma once
#include "treenode.hpp"
using namespace std;

template <typename T, bool WithParent = false, template<typename, bool> class N = Node>
class Tree {
public:
    using NodePtr = typename N<T, WithParent>::NodePtr;

    const NodePtr &getRoot() const {
        if (isEmpty())
            throw TreeIsEmptyException();
        return root;
    }

    template <typename U>
    void setRoot(U &&node) { root = forward<U>(node); }

    bool isEmpty() const { return !root; }

    class TreeIsEmptyException {};
protected:
    NodePtr root;
};

template <typename T, bool WithParent = false>
using NodePtr = typename Tree<T, WithParent>::NodePtr;


/* treetestutils.hpp */
#pragma once
#include <limits>
#include <algorithm>
#include <functional>
#include <queue>
#include <iostream>
#include <iomanip>
#include <memory>
using namespace std;

template <typename T, bool NodeWithParent, template<typename, bool> class Node>
class Tree;

template <typename T, bool WithParent>
class Node;

namespace TestUtils {
    template <typename T, bool NodeWithParent, template<typename, bool> class Node>
    void printTree(const Tree<T, NodeWithParent, Node> &tree) {
        using NodePtr = typename Tree<T, NodeWithParent, Node>::NodePtr;

        T minValue = numeric_limits<T>::max(), maxValue = numeric_limits<T>::min();

        // Lambda function is used to hide it from externall access
        function<size_t (const NodePtr &)> getDepth =
        [&](const NodePtr &node) -> size_t {
            if (!node)
                return 0;

            auto depth = max(getDepth(node->getLeft()), getDepth(node->getRight())) + 1;
            minValue = min(minValue, node->getValue());
            maxValue = max(maxValue, node->getValue());
            return depth;
        };

        size_t depth = getDepth(tree.getRoot());

        // bottommost max leaf count
        size_t size = pow(2, depth - 1);

        // width of node, in digits
        size_t digits = (maxValue != 0 || minValue != 0) ? log10(max(maxValue, abs(minValue))) + 1  : 1;
        if (minValue < 0)
            ++digits;

        const string placeholder(digits, ' ');

        queue<NodePtr> queue;
        queue<NodePtr> childs;
        queue.push(tree.getRoot());
        cout << "Tree:" << endl;

        do {
            // space between nodes
            string space((size - 1) * (placeholder.length() + 1) + 1, ' ');

            // margin
            cout << string(space.length() / 2, ' ');;
            while (!queue.empty()) {
                if (!queue.front()) {
                    cout << placeholder << space;
                    childs.emplace();
                    childs.emplace();
                } else {
                    cout << setw(digits) << right << queue.front()->getValue() << space;
                    childs.push(queue.front()->getLeft());
                    childs.push(queue.front()->getRight());
                }
                queue.pop();
            }
            cout << endl;
            queue.swap(childs);
            size /= 2;
        } while (size > 0);
    }

    // The function treeFromArray from the task 4.2 helps us to fill test trees.
    template <typename T, bool NodeWithParent = false, template<typename, bool> class N = Node>
    auto treeFromArray(const T *array, size_t size) {
        using NodePtr = typename Tree<T, NodeWithParent, N>::NodePtr;

        function<NodePtr (const T *, const NodePtr &, int, int)> subtreeFromArray =
        [&subtreeFromArray](const T *array, const NodePtr &parent, int start, int end) -> NodePtr {
            if (end < start)
                return nullptr;

            int i = (start + end) / 2;
            auto node = make_shared<N<T, NodeWithParent>>(array[i], parent);
            node->setLeftChild(subtreeFromArray(array, node, start, i - 1));
            node->setRightChild(subtreeFromArray(array, node, i + 1, end));
            return node;
        };

        Tree<T, NodeWithParent, N> tree;
        tree.setRoot(subtreeFromArray(&array[0], nullptr, 0, size - 1));
        return tree;
    }

    template <typename T, bool NodeWithParent = false, template<typename, bool> class N = Node>
    auto treeFromArray(initializer_list<T> array) {
        return treeFromArray<T, NodeWithParent, N>(array.begin(), array.size());
    }

    template <typename T, bool NodeWithParent = false, template<typename, bool> class N = Node>
    auto getSampleTree(size_t nodeCount) {
        vector<T> v(nodeCount) ;
        iota(begin(v), end(v), 0); // Fill with 0, 1, ..., nodeCount - 1.
        return treeFromArray<T, NodeWithParent, N>(&v[0], v.size());
    }
}


/* ListOfDepth.cpp */
#include <list>
#include "tree.hpp"
#include "treetestutils.hpp"
using namespace std;

template <typename T>
using ListOfDepths = list<list<NodePtr<T>>>;

template <typename T>
ListOfDepths<T> getListOfDepths(const Tree<T> &tree) {
    ListOfDepths<T> result;

    result.emplace_back();
    auto list = &result.back();
    list->push_back(tree.getRoot());

    do {
        result.emplace_back();
        auto &childs = result.back();
        for (const auto &n : *list) {
            if (n->getLeft())
                childs.push_back(n->getLeft());
            if (n->getRight())
                childs.push_back(n->getRight());
        }
        if (childs.empty()) {
            result.pop_back();
            break;
        }
        list = &childs;
    } while (true);

    return result;
}

template <typename T>
void printDepths(const ListOfDepths<T> &depths) {
    cout << "Nodes: " << endl;
    int depth = 0;
    for (const auto &line : depths) {
        cout << depth << ": ";
        auto sep = "";
        for (const auto &n : line) {
            cout << sep << n->getValue();
            sep = ", ";
        }
        cout << endl;
        ++depth;
    }
    cout << endl;
}

int main() {
    auto tree = TestUtils::getSampleTree<int>(15);
    TestUtils::printTree(tree);
    auto depths = getListOfDepths(tree);
    printDepths<int>(depths);

    tree = TestUtils::getSampleTree<int>(20);
    TestUtils::printTree(tree);
    depths = getListOfDepths(tree);
    printDepths<int>(depths);
    return 0;
}
