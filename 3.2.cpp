/* stack.hpp */
#include <utility>
using namespace std;

template <typename T>
class Stack {
public:
    Stack() : top(nullptr), stackSize(0) { }

    Stack(Stack &&other) : top(move(other.top)), stackSize(move(other.stackSize)) { }

    ~Stack() {
        while (!isEmpty())
            pop();
    }

    template <typename U>
    void push(U &&value) {
        auto n = new Node(forward<U>(value), top);
        top = n;
        ++stackSize;
    }

    T &peek() {
        if (!top)
            throw StackIsEmptyException();
        return top->value;
    }

    T pop() {
        if (!top)
            throw StackIsEmptyException();
        auto value(move(top->value));
        auto n = top;
        top = n->next;
        delete n;
        --stackSize;
        return value;
    }

    bool isEmpty() const {
        return !top;
    }

    size_t size() const {
        return stackSize;
    }

    class StackIsEmptyException { };

private:
    struct Node {
        Node(T &&v, Node *n): value(move(v)), next(n) { }
        Node(const T &v, Node *n): value(v), next(n) { }

        T value;
        Node *next;
    };

    Node *top;
    size_t stackSize;
};

/* stackMin.cpp */
#include <iostream>
#include "stack.hpp"
using namespace std;

template<typename T>
class StackMin {
public:
    template<typename U>
    void push(U &&value) {
        if (minStack.isEmpty() || value <= minStack.peek())
            minStack.push(value);
        stack.push(forward<U>(value));
    }

    T &peek() {
        return stack.peek();
    }

    T &min() {
        return minStack.peek();
    }

    T pop() {
        auto value = stack.pop();
        if (value == min())
            minStack.pop();
        return value;
    }

    bool isEmpty() {
        return stack.isEmpty();
    }

private:
    Stack<T> stack;
    Stack<T> minStack;
};

int main() {
    StackMin<int> stack;
    for (auto v : {5, 10, 4, 9, 3, 3, 8, 2, 2, 7, 6}) {
        stack.push(v);
        cout << "Pushed value: " << v << ", min value: " << stack.min() << endl;
    }
    while (!stack.isEmpty()) {
        auto v = stack.pop();
        cout << "Popped value: " << v;
        if (stack.isEmpty())
            cout << ", stack is empty" << endl;
        else
            cout << ", min value: " << stack.min() << endl;
    }
    return 0;
}
