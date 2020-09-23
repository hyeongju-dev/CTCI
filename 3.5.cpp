#include <iostream>
#include "stack.hpp"
using namespace std;

template <typename T>
class SortedStack {
public:
    SortedStack() : sorted(false) { }

    template <typename U>
    void push(U &&value) {
        stack.push(forward<U>(value));
        sorted = false;
    }

    T &peek() {
        sort();
        return stack.peek();
    }

    T pop() {
        sort();
        return stack.pop();
    }

    bool isEmpty() const {
        return stack.isEmpty();
    }

private:
    void sort() {
        if (sorted)
            return;

        Stack<T> helper;
        while (!stack.isEmpty()) {
            T value = stack.pop();

            while (!helper.isEmpty() && value < helper.peek())
                stack.push(helper.pop());

            helper.push(move(value));
        }

        while (!helper.isEmpty())
            stack.push(helper.pop());
        sorted = true;
    }

    Stack<T> stack;
    bool sorted;
};

int main() {
    SortedStack<int> stack;
    for (auto v : {5, 10, 4, 9, 3, 3, 8, 1, 2, 2, 7, 6}) {
        stack.push(v);
        cout << "Pushed value: " << v << endl;
    }

    while (!stack.isEmpty()) {
        auto v = stack.pop();
        cout << "Popped value: " << v << endl;
    }

    return 0;
}
