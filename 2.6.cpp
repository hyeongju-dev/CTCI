// prefer struct/class over pair<,> for MRO

#include <iostream>
#include <stack>
using namespace std;

struct Node {
  int data;
  Node* next;
  Node (int d) : data{ d }, next{ nullptr } { }
};

void insert(Node*& head, int data) {
  Node* newNode = new Node(data);
  newNode->next = head;
  head = newNode;
}

void printList(Node* head) {
  while (head) {
    cout << head->data << " --> ";
    head = head->next;
  }
  cout << "nullptr" << endl;
}

void reverse(Node*& head) {
  if (head == nullptr  || (head && (head->next == nullptr)))
    return;

  Node* newHead = nullptr;
  Node* nextNode = nullptr;
  while (head) {
    nextNode = head->next;
    head->next = newHead;
    newHead = head;
    head = nextNode;
  }
  head = newHead;
}


/* Iteratively determine if list is palindrome using reversing the list */
bool isPalindromeIterative1(Node* head) {
  if (head == nullptr || head->next == nullptr)
    return true;

  Node* ptr1 = head;
  Node* ptr2 = head;
  Node* middleNode = nullptr;

  while (ptr2 && ptr1 && ptr1->next) {
    ptr1 = ptr1->next->next;
    ptr2 = ptr2->next;
  }

  if (ptr1 && ptr1->next == nullptr)
    ptr2 = ptr2->next;

  reverse(ptr2);
  middleNode = ptr2;

  ptr1 = head;

  while (ptr1 && ptr2 && ptr1->data == ptr2->data) {
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }

  reverse(middleNode);

  if (ptr2 == nullptr)
    return true;
  else
    return false;
}

/* Iteratively determine if list is palindrome using a stack */
bool isPalindromeIterative2(Node* head) {
  if (head == nullptr || head->next == nullptr)
    return true;

  Node* ptr1 = head;
  Node* ptr2 = head;

  stack<Node*> nodeStack;

  while (ptr2 && ptr1 && ptr1->next) {
    ptr1 = ptr1->next->next;
    nodeStack.push(ptr2);
    ptr2 = ptr2->next;
  }

  if (ptr1 && ptr1->next == nullptr)
    ptr2 = ptr2->next;

  while (!nodeStack.empty() && ptr2) {
    Node* curr = nodeStack.top();
    nodeStack.pop();
    if (curr->data != ptr2->data)
      return false;
    ptr2 = ptr2->next;
  }

  return true;
}


/* Recursive approach to determine if list is palindrome :: using two pointers */
bool isPalindromeRecursive(Node*& left, Node* right) {  // it's helper
  if (right == nullptr)
    return true;

  bool isPalindrome = isPalindromeRecursive(left, right->next);
  if (!isPalindrome)
    return false;

  isPalindrome = (left->data == right->data);

  left = left->next;

  return isPalindrome;
}

bool isPalindromeRecursive(Node* head) {
  return isPalindromeRecursive(head, head);   // oop - overload
}


int main() {
  Node* head1 = nullptr;
  insert(head1, 'a'); insert(head1, 'b'); insert(head1, 'c');
  insert(head1, 'c'); insert(head1, 'b'); insert(head1, 'a');
  cout << "List 1: "; printList(head1);
  if (isPalindromeIterative1(head1))
    cout << "List 1 is pallindrome list" << endl;
  else
    cout << "List 1 is not a pallindrome list" << endl;

  // TODO: call the other methods - especially for any odd case

  return 0;
}
