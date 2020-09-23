/* queue.hpp */
#include <utility>

template <typename T>
class Queue {
public:
    Queue() : first(nullptr), last(nullptr), queueSize(0) { }
    Queue(Queue &&other) : first(move(other.first)), last(move(other.last)), queueSize(move(other.queueSize)) { }

    ~Queue() {
        while (!isEmpty())
            remove();
    }

    template <typename U>
    void add(U &&value) {
        auto n = new Node(forward<U>(value));
        if (!first)
            first = n;
        else
            last->next = n;
        last = n;
        ++queueSize;
    }

    T &peek() {
        if (!first)
            throw QueueIsEmptyException();
        return first->value;
    }

    T remove() {
        if (!first)
            throw QueueIsEmptyException();
        auto value(move(first->value));
        auto n = first;
        first = n->next;
        if (!first)
            last = nullptr;
        delete n;
        --queueSize;
        return value;
    }

    bool isEmpty() const {
        return !first;
    }

    size_t size() const {
        return queueSize;
    }

    class QueueIsEmptyException { };

private:
    struct Node {
        Node(T &&v): value(move(v)), next(nullptr) { }
        T value;
        Node *next;
    };

    Node *first;
    Node *last;
    size_t queueSize;
};


/* animalShelter.cpp */
#include <iostream>
#include <limits>
#include <memory>
#include "queue.hpp"
using namespace std;

class Animal {
protected:
    Animal(string &&animalName) : name(move(animalName)) {
        orderNo = numeric_limits<decltype(orderNo)>::max();
    }

public:
    virtual ~Animal() { }

    void setOrder(size_t order) {
        orderNo = order;
    }

    size_t getOrder() const {
        return orderNo;
    }

    const string &getName() const {
        return name;
    }

    bool operator < (const Animal &other) { // operator overloading in C++
        return orderNo < other.orderNo;
    }

    template <typename T>
    static shared_ptr<Animal> create(string &&name) {
        return make_shared<T>(move(name));
    }

private:
    string name;
    size_t orderNo; // timestamp
};

class Dog: public Animal {
public:
    Dog(string &&name) : Animal(move(name)) { }
};
class Cat: public Animal {
public:
    Cat(string &&name) : Animal(move(name)) { }
};

class Shelter {
public:
    Shelter() : nextOrderNo(0) { }

    void enqueue(shared_ptr<Animal> &&animal) {
        if (auto dog = dynamic_pointer_cast<Dog>(animal)) {
            dog->setOrder(nextOrderNo++);
            dogs.add(move(dog));
        } else if (auto cat = dynamic_pointer_cast<Cat>(animal)) {
            cat->setOrder(nextOrderNo++);
            cats.add(move(cat));
        } else
            throw BadAnimalException();
    }

    shared_ptr<Animal> dequeueAny() {
        if (dogs.isEmpty())
            return dequeueCat();
        else if (cats.isEmpty())
            return dequeueDog();
        else if (*dogs.peek() < *cats.peek())
            return dequeueDog();
        else
            return dequeueCat();
    }

    shared_ptr<Animal> dequeueCat() {
        return static_pointer_cast<Animal>(cats.remove());
    }

    shared_ptr<Animal> dequeueDog() {
        return static_pointer_cast<Animal>(dogs.remove());
    }

    class BadAnimalException {};

private:
    Queue<shared_ptr<Dog>> dogs;
    Queue<shared_ptr<Cat>> cats;
    size_t nextOrderNo;
};

int main() {
    Shelter shelter;
    for (auto name : {"Dog 1", "Cat 1", "Dog 2", "Dog 3 ", "Cat 2", "Cat 3", "Cat 4", "Dog 4", "Dog 5", "Dog 6", "Cat 5", "Cat 6", "Dog 7", "Dog 8", "Cat 7", "Dog 9"}) {
        if (name[0] == 'D')
            shelter.enqueue(Animal::create<Dog>(move(name)));
        else if (name[0] == 'C')
            shelter.enqueue(Animal::create<Cat>(move(name)));
    }

    cout << "any --> " << shelter.dequeueAny()->getName() << endl;
    cout << "any --> " << shelter.dequeueAny()->getName() << endl;

    cout << "dog --> " << shelter.dequeueDog()->getName() << endl;
    cout << "cat --> " << shelter.dequeueCat()->getName() << endl;
    cout << "cat --> " << shelter.dequeueCat()->getName() << endl;
    cout << "cat --> " << shelter.dequeueCat()->getName() << endl;
    cout << "cat --> " << shelter.dequeueCat()->getName() << endl;
    cout << "dog --> " << shelter.dequeueDog()->getName() << endl;
    cout << "dog --> " << shelter.dequeueDog()->getName() << endl;
    cout << "cat --> " << shelter.dequeueCat()->getName() << endl;
    cout << "any --> " << shelter.dequeueAny()->getName() << endl;
    return 0;
}
