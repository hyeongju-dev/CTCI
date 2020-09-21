#include <iostream>
#include <cmath>
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

int length(Node* head) {
  int count = 0;
  while (head) {
    head = head->next;
    count++;
  }
  return count;
}


Node* intersectionPoint(Node* head1, Node* head2) {
  int len1 = length(head1);
  int len2 = length(head2);

  Node* ptr1 = (len1 > len2 ? head1 : head2);
  Node* ptr2 = (len1 > len2 ? head2 : head1);
  int i = 0;
  while (i < abs(len1-len2) && ptr1) {
    ptr1 = ptr1->next;
    ++i;
  }

  // Now we have equal nodes to travel on both the nodes. let's traverse and compare the pointers
  while (ptr1 && ptr2) {
    if (ptr1 == ptr2)
      return ptr1;
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }

  return nullptr; // if there's no intersection point
}


int main() {
  Node* list1 = new Node(3);
  list1->next = new Node(6);
  list1->next->next = new Node(9);
  list1->next->next->next = new Node(12);
  list1->next->next->next->next = new Node(15);
  list1->next->next->next->next->next = new Node(18);

  Node* list2 = new Node(7);
  list2->next = new Node(10);
  list2->next->next = list1->next->next->next;

  printList(list1);
  printList(list2);

  Node* intersectingNode = intersectionPoint(list1 , list2);
  if (intersectingNode)
    cout << "Intersecting Node of lists is :" << intersectingNode->data << endl;
  else
    cout << "Lists do not interset" << endl;

  return 0;
}
