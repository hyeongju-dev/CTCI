#include <iostream>
using namespace std;

struct Node {
  int data;
  Node * next;
  Node(int d) : data{ d }, next{ nullptr } { }
};

void insert(Node *&head, int data) {
  Node *newNode = new Node(data);
  newNode->next = head;
  head = newNode;
}

void deleteList(Node *&head) {
  Node *nextNode;
  while (head) {
    nextNode = head->next;
    delete(head);
    head = nextNode;
  }
}

void printList(Node *head) {
  while (head) {
    cout << head->data << " --> ";
    head = head->next;
  }
  cout << "null" << endl;
}


Node* kthToLastRecursive(Node *head, int k , int &i) {
  if (head == nullptr)
    return nullptr;

  Node *node = kthToLastHelper(head->next, k, i);
  i = i+1;
  if (i == k)
    return head;
  return node;
}

Node* kthToLastRecursive(Node * head, int k) {
  int i = 0;
  return kthToLastRecursive(head, k, i);
}


Node* kthToLastIterative(Node *head, int k) {
  if (head == nullptr)
    return head;

  Node *fast = head;
  Node *slow = head;

  int i = 0;
  while (i < k && fast) {
    fast = fast->next;
    ++i;
  }

  if (i < k)        // out of bounds
    return nullptr;

  while (fast != nullptr) {
    fast = fast->next;
    slow = slow->next;
  }

  return slow;
}


int main() {
  Node * head = nullptr;
  for (int i = 7; i > 0; --i)
    insert(head, i);
  cout << "List: ";
  printList(head);

  cout << "4th node from last (Recursive): ";
  Node *node4 = kthToLastRecursive(head, 4);
  if (node4 != nullptr)
    cout << node4->data << endl;
  else
    cout << "NULL NODE" << endl;

  cout << "4th node from last (Iterative): ";
  node4 = kthToLastIterative(head, 4);
  if (node4 != nullptr)
    cout << node4->data << endl;
  else
    cout << "NULL NODE" << endl;

  deleteList(head);

  return 0;
}
