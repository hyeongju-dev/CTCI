#include <memory>
#include <array>
#include <vector>
#include "tree.hpp"
#include "treetestutils.hpp"
using namespace std;

template <typename T, bool>
class RandomNode;

template <typename T, bool NotUsed = false>
class RandomNode {
public:
    using NodePtr = shared_ptr<RandomNode<T>>;

    RandomNode(const T &v): size(1) { value = v; }

    const NodePtr &getLeft() const { return childs[0]; }

    const NodePtr &getRight() const { return childs[1]; }

    const T &getValue() const { return value; }

private:
    void add(const T &v) {
        if (!childs[v > value])
            childs[v > value] = make_shared<RandomNode<T>>(v);
        else
            childs[v > value]->add(v);
        ++size;
    }

    const T &getRandom() const { return get(rand() % size + 1); }

    const T &get(size_t n) const {
        if (n == size)
            return value;
        else if (childs[0] && n <= childs[0]->size)
            return childs[0]->get(n);
        else
            return childs[1]->get(n - (childs[0] ? childs[0]->size : 0));
    }

    T value;
    size_t size;
    array<NodePtr, 2> childs;

    template <typename U>
    friend class RandomTree;
};

template <typename T>
class RandomTree : public Tree<T, false, RandomNode> {
    using Base = Tree<T, false, RandomNode>;

public:
    const T &getRandom() const {
        if (!Base::root)
            throw typename Base::TreeIsEmptyException();
        return Base::root->getRandom();
    }

    void add(const T &value) {
        if (Base::root)
            Base::root->add(value);
        else
            Base::root = make_shared<RandomNode<T, false>>(value);
    }
};


int main() {
    srand (unsigned(time(0)));
    vector<int> v(7) ;
    iota(begin(v), end(v), 0); // Fill with 0, 1, ..., nodeCount - 1.
    random_shuffle(begin(v), end(v), [](int i){return rand() % i;});

    RandomTree<int> tree;
    tree.add(v.back());
    v.pop_back();
    for (auto i : v)
        tree.add(i);

    TestUtils::printTree(tree);
    cout << endl;

    // Check distribution of rundom tree nodes
    v = vector<int>(v.size() + 1, 0);
    for (auto i = 0U; i < v.size() * 1000; ++i)
        ++v[tree.getRandom()];

    size_t cnt = accumulate(v.begin(), v.end(), 0);
    cout << "Total: " << cnt << " times\n";
    cout << fixed << setprecision(2);
    for (auto i = 0U; i < v.size(); ++i)
        cout << i << ": " << 100.0 * v[i] / cnt << "%\n";
}
