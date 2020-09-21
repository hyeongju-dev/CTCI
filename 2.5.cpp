#include <iostream>
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

void deleteList(Node*& head) {
   Node* nextNode;
   while (head) {
     nextNode = head->next;
     delete(head);
     head = nextNode;
   }
}


Node* add_iterative(Node* list1, Node* list2) {
  if (list1 == nullptr)
    return list2;
  if (list2 == nullptr)
    return list1;

  Node* list3 = nullptr;
  Node* list3Tail = nullptr;

  int value = 0, carry = 0;

  while (list1 || list2) {
    value = carry + (list1 ? list1->data : 0 ) + (list2 ? list2->data : 0);

    if (value > 9) {
      carry = 1;
      value = value % 10;
    } else {
      carry = 0;
    }

    Node* temp = new Node(value);

    if (list3 == nullptr)
      list3 = temp;
    else
      list3Tail->next = temp;

    list3Tail = temp;

    if (list1)
      list1 = list1->next;
    if (list2)
      list2 = list2->next;
  }

  if (carry > 0)
    list3Tail->next = new Node(carry);

  return list3;
}

Node* add_recursive(Node* list1, Node* list2, int carry) {
  if (list1 == nullptr && list2 == nullptr && carry == 0)
    return nullptr;

  int value = carry;
  if (list1)
    value += list1->data;
  if (list2)
    value += list2->data;

  Node* resultNode = new Node(value % 10);

  resultNode->next = add_recursive(list1 ? (list1->next) : nullptr,
                                   list2 ? (list2->next) : nullptr,
                                   value > 9 ? 1 : 0);
  return resultNode;
}


/* Follow up part: Lists are stored such that 1's digit is at the tail of list */
void padList(Node*& list, int padding) {  // helper routine for padding the shorter list
  for (int i = 0; i < padding; ++i)
    insert(list, 0);
}

int length(Node* head) {  // helper routine to return length of list
  int len = 0;
  while (head) {
    len++;
    head = head->next;
  }
  return len;
}

Node* add_followup_helper(Node* list1, Node* list2, int& carry) {
  if (list1 == nullptr && list2 == nullptr && carry == 0)
    return nullptr;

  Node* result = add_followup_helper(list1 ? (list1->next) : nullptr,
                                     list2 ? (list2->next) : nullptr,
                                     carry);

  int value = carry + (list1 ? list1->data : 0) + (list2 ? list2->data : 0);
  insert(result, value % 10);
  carry = (value > 9 ? 1 : 0);
  return result;
}

Node * add_followup( Node * list1, Node * list2 ) {
  // adding list such that 1's digit is at tail (follow up part of question)
  int len1 = length(list1);
  int len2 = length(list2);

  if (len1 > len2) // pad the smaller list
    padList(list2, len1 - len2);
  else
    padList(list1, len2 - len1);

  int carry = 0;
  Node* list3 = add_followup_helper(list1, list2, carry);
  if (carry)
    insert(list3, carry);

  return list3;
}


int main() {
  Node* list1 = nullptr;  // making list 1 for number 617
  insert(list1, 6); insert(list1, 1); insert(list1, 7);
  cout << "List1:  "; printList(list1);

  Node* list2 = nullptr;  // making list2 for number 295
  insert(list2, 2); insert(list2, 9); insert(list2, 5);
  cout << "List2:  "; printList(list2);

  Node* list3 = add_iterative(list1, list2);
  cout << "Iterative Solution: " << endl;
  cout << "List3:  "; printList(list3);

  Node* list4 = add_recursive(list1, list2, 0);
  cout << "Recursive Solution: " << endl;
  cout << "List4:  "; printList(list4);

  deleteList(list1); deleteList(list2); deleteList(list3); deleteList(list4);

  // TODO: call the add function related to follow-up

  return 0;
}
