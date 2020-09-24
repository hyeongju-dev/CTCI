/* graph.hpp */
#pragma once

#include <deque>
#include <memory>
#include <unordered_set>
#include <unordered_map>
using namespace std;

template<typename T>
struct WeakPtrHash : public unary_function<weak_ptr<T>, size_t> {
    size_t operator()(const weak_ptr<T>& wp) const {
        auto sp = wp.lock();
        return hash<decltype(sp)>()(sp);
    }
};

template<typename T>
struct WeakPtrEqual : public unary_function<weak_ptr<T>, bool> {
    bool operator()(const weak_ptr<T>& left, const weak_ptr<T>& right) const {
        return !left.owner_before(right) && !right.owner_before(left);
    }
};

template <typename State>
class Graph {
public:
    class Node {
    public:
        Node(const string &n) : name(n) {}
        virtual ~Node() {}

        bool isAdjacentFor(const shared_ptr<Node> &other) const {
            return childs.find(other) != childs.end();
        }

        void addChild(const shared_ptr<Node> &other) {
            childs.insert(other);
        }

        const unordered_set<weak_ptr<Node>, WeakPtrHash<Node>, WeakPtrEqual<Node>> &getAdjacent() const {
            return childs;
        }

        const string &Name() const {
            return name;
        }

        mutable State state;
        string name;

    private:
        unordered_set<weak_ptr<Node>, WeakPtrHash<Node>, WeakPtrEqual<Node>> childs;
    };

    bool matrix(size_t i, size_t j) const {
        if (i == j)
            return false;

        const auto &s = nodes[i];
        const auto &d = nodes[j];
        return s->isAdjacentFor(d);
    }

    shared_ptr<Node> &addNode(const string &name = string()) {
        nodes.emplace_back(make_shared<Node>(name));
        if (!name.empty())
            namedNodes[name] = nodes.back();
        return nodes.back();
    }

    const shared_ptr<Node> &operator[] (size_t i) const {
        return nodes[i];
    }

    const shared_ptr<Node> &operator[] (const string &name) const {
        return namedNodes.at(name);
    }

    const deque<shared_ptr<Node>> &getNodes() const {
        return nodes;
    }

private:
    deque<shared_ptr<Node>> nodes;
    unordered_map<string, shared_ptr<Node>> namedNodes;
};

template <typename State>
using Node = shared_ptr<typename Graph<State>::Node>;


/* graphtestutils.hpp */
#pragma once

#include "graph.hpp"
using namespace std;

namespace TestUtils {
    template<typename State>
    Graph<State> createGraph(initializer_list<string> projects, initializer_list<array<const string, 2>> deps) {
        Graph<State> graph;
        for (auto &n : projects)
            graph.addNode(n)->state = static_cast<State>(0);
        for (auto &d : deps)
            graph[d[0]]->addChild(graph[d[1]]);
        return graph;
    }

    template <typename State>
    Graph<State> getExampleGraph() {
        return createGraph<State>({"0", "1", "2", "3", "4", "5", "6"},
            {{"0", "1"}, {"1", "2"}, {"2", "0"}, {"2", "3"}, {"3", "2"}, {"4", "6"}, {"5", "4"}, {"6", "5"}});
    }

    template <typename State>
    Graph<State> getExampleGraph2() {
        return createGraph<State>({"0", "1", "2", "3"},
            {{"0", "1"}, {"1", "2"}, {"2", "0"}, {"3", "2"}});
    }

    template <typename State>
    Graph<State> getExampleGraph3() {
        return createGraph<State>({"0", "1", "2", "3", "4", "5"},
            {{"0", "1"}, {"0", "4"}, {"0", "5"}, {"1", "3"}, {"1", "4"}, {"2", "1"}, {"3", "2"}, {"3", "4"}});
    }
}

/* routeBetweenNodes.cpp */
#include <queue>
#include <iostream>
#include <cassert>
#include "graph.hpp"
#include "graphtestutils.hpp"
using namespace std;

enum State {Unvisited, Visiting, Visited};

// Width visiting <= BFS, Breadth-First Search
bool routeBetwenNodes(const Graph<State> &graph, const Node<State> &from, const Node<State> &to) {
    if (from == to)
        return true;

    for (auto &n : graph.getNodes())
        n->state = Unvisited;

    queue<Node<State>> queue;

    from->state = Visiting;
    queue.push(from);

    while (!queue.empty()) {
        Node<State> n = queue.front();
        queue.pop();
        for (auto &c : n->getAdjacent()) {
            auto v = c.lock();
            if (v && v->state == Unvisited) {
                if (v == to)
                    return true;
                else {
                    v->state = Visiting;
                    queue.push(v);
                }
            }
        }
        n->state = Visited;
    }
    return false;
}

// Recursive visiting <= DFS, Depth-First Search
bool routeBetwenNodesWalker(const Graph<State> &graph, const Node<State> &from, const Node<State> &to) {
    if (from == to)
        return true;

    from->state = Visited;

    for (auto &c : from->getAdjacent()) {
        auto node = c.lock();
        if (node && node->state != Visited) {
            if (routeBetwenNodesWalker(graph, node, to))
                return true;
        }
    }
    return false;
}

bool routeBetwenNodesR(const Graph<State> &graph, const Node<State> &from, const Node<State> &to) {
    for (auto &n : graph.getNodes())
        n->state = Unvisited;

    return routeBetwenNodesWalker(graph, from, to);
}

bool test(const Graph<State> &graph, size_t from, size_t to) {
    auto &fromNode = graph[from], &toNode = graph[to];
    bool result = routeBetwenNodes(graph, fromNode, toNode);
    bool resultR = routeBetwenNodesR(graph, fromNode, toNode);

    assert(result == resultR);
    cout << toNode->Name() << " is " << (result ? "" : "NOT ") << "reachable from " << fromNode->Name() << endl;
    cout << toNode->Name() << " is " << (resultR ? "" : "NOT ") << "reachable from " << fromNode->Name() << endl;
    return result;
}

void testGraph(const Graph<State> &graph) {
    auto size = graph.getNodes().size();
    for (decltype(size) i = 0; i < size; ++i) {
        for (decltype(size) j = 0; j < size; ++j)
            test(graph, i, j);
        cout << endl;
    }

}

int main() {
    testGraph(TestUtils::getExampleGraph<State>());
    testGraph(TestUtils::getExampleGraph2<State>());
    testGraph(TestUtils::getExampleGraph3<State>());
    return 0;
}
