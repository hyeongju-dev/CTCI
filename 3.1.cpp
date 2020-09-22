#include <iostream>
#include <cstdlib>
using namespace std;

// TODO: actually this class definition code should be included in header file named "FixedMultiStack.hpp"
class FixedMultiStack {
public:
  // Create 3 stacks, each stack is of size stackCapacity
  FixedMultiStack(int stackCapacity);
  virtual ~FixedMultiStack();

  void push(int stackNum, int value);   // stackNum is from 0 to 2
  void pop(int stackNum);
  int top(int stackNum) const;
  bool isEmpty(int stackNum) const;
  bool isFull(int stackNum) const;

private:
  int numOfStack = 3;
  int stackCapacity;
  int *stackArray;        // not [] but * :: for dynamic memory allocation
  int *stackCapacityUsed;

  int indexOfTop(int stackNum) const;
};


FixedMultiStack::FixedMultiStack(int stackCapacity) {
  this->stackCapacity = stackCapacity;
  stackArray = new int[numOfStack * stackCapacity]();
  stackCapacityUsed = new int[numOfStack]();
}

FixedMultiStack::~FixedMultiStack() {
  delete [] stackArray;
  delete [] stackCapacityUsed;
}

void FixedMultiStack::push(int stackNum, int value) {
  if (isFull(stackNum)) {
    cout << "Stack " << stackNum << " is full." << endl;  // or throw FullStackException();
  } else {
    stackCapacityUsed[stackNum]++;
    stackArray[indexOfTop(stackNum)] = value;
  }
}

void FixedMultiStack::pop(int stackNum) {
  if (isEmpty(stackNum)) {
    cout << "Stack " << stackNum << " is empty." << endl;
  } else {
    int topIndex = indexOfTop(stackNum);
    stackArray[topIndex] = 0;
    stackCapacityUsed[stackNum]--;
  }
}

int FixedMultiStack::top(int stackNum) const
  if (isEmpty(stackNum)) {
    cout << "Stack " << stackNum << " is empty." << endl;
    exit(1); // or throw an exception
  } else {
    return stackArray[indexOfTop(stackNum)];
  }
}

bool FixedMultiStack::isEmpty(int stackNum) const {
  return (stackCapacityUsed[stackNum] == 0);
}

bool FixedMultiStack::isFull(int stackNum) const {
  return (stackCapacityUsed[stackNum] == stackCapacity);
}

int FixedMultiStack::indexOfTop(int stackNum) const {
  int startIndex = stackNum * stackCapacity;
  int capacity = stackCapacityUsed[stackNum];
  return (startIndex + capacity - 1);
}
