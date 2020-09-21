#include <iostream>
#include <random>
using namespace std;

struct Node {
  int data;
  Node *next;
  Node(int d) : data{ d }, next{ nullptr } { }
};

void insert(Node*& head, int data) {
  Node* newNode = new Node(data);
  if (head == nullptr) {
    head = newNode;
  } else {
    Node* curr = head;
    while (curr->next)
      curr = curr->next;
    curr->next = newNode;
  }
}

void printList(Node* head) {
  while (head) {
    cout << head->data << " --> ";
    head = head->next;
  }
  cout << "nullptr" << endl;
}


Node* partition(Node* listhead, int x) {
   Node* head = nullptr;
   Node* headInitial = nullptr;
   Node* tail = nullptr;
   Node* tailInitial = nullptr;
   Node* curr = listhead;

   while (curr != nullptr) {
     Node* nextNode = curr->next;
     if (curr->data < x) {
        if (head == nullptr) {
          head = curr;
          headInitial = head;
        }
        head->next = curr;
        head = curr;
     } else {
        if (tail == nullptr) {
          tail = curr;
          tailInitial = tail;
        }
        tail->next = curr;
        tail = curr;
     }
     curr = nextNode;
   }

   head->next = tailInitial;
   tail->next = nullptr;

   return headInitial;
}


// if you don't need to keep the list stable, you can use the code below (cuz it's simpler):
Node* partition2(Node* listhead, int x) {
  Node* head = head;
  Node* tail = head;
  Node* curr = listhead;

  while (curr != nullptr) {
    Node* nextNode = curr->next;
    if (curr->data < x) {
      curr->next = head;
      head = curr;
    } else {
      tail->next = curr;
      tail = curr;
    }
    curr = nextNode;
  }
  tail->next = nullptr;

  return head;
}

int main() {
  Node *head = nullptr;
  for (int i = 0; i < 10; ++i)
		insert(head, rand()%9);

  cout << "List before partition around 5:\n";
  printList(head);
  cout << "List after partition around 5:\n";
  printList(partition(head, 5));

  return 0;
}
