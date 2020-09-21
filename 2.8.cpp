// I have already solved this problem as a homework in '20 spring [TOPICS IN ALGORITHMS] class

/*
fastRunner & slowRunner 접근법을 이용한다: slowRunner가 한 번 전진할 때, fastRunner는 두 번 전진한다.
"두 포인터의 충돌이 발생하는 지점"과 "링크드 리스트의 헤드"는 모두 루프 시작점으로부터 '연결 리스트 루프가 아닌 부분의 크기의 노드 수(k)' 만큼 떨어져 있다.
즉, 충돌 발생 지점에서 하나의 포인터만을 링크드 리스트 헤드를 가리키도록 옮기면, 루프 시작점으로부터 두 노드들은 모두 동일한 크기 만큼 떨어지게 된다.
따라서 두 포인터를 같은 속도로 한 번에 한 칸씩 움직이면, k 스텝 이후 루프 시작점에서 다시 충돌한다. 이 노드가 바로 루프의 시작점이다.

연결 리스트의 전체 노드 수인 n의 일부에 불과한 k를 이용해 선형적으로 전진하는 방식으로 루프의 시작 부분을 찾으므로, 해당 알고리즘은 O(n)의 시간 복잡도를 지닌다.
*/

#include <iostream>
#include <vector>
using namespace std;

class FindBeginning {
public:
  class Node {
  public:
    int data;
    Node* next;
    Node(int data) {
      this->data = data;
      this->next = nullptr;
    }
  };
  Node* head;
  int size;

  FindBeginning() {
    this->head = nullptr;
    this->size = 0;
  }

  void addNode(int data) {
    if (head == nullptr)
      head = new Node(data);
    else {
      Node* tmp = head;
      while (tmp->next != nullptr)
        tmp = tmp->next;
      tmp->next = new Node(data);
    }
    size++;
  }

  void makeLoop(int idx) {
    if (idx < 0 || idx >= size) {
      cout << "인덱스가 범위를 벗어나, 루프를 생성할 수 없습니다." << endl;
      return;
    }

    Node* tmp1 = head;
    Node* tmp2 = head;

    for (int i = 0; i < idx; ++i)
      tmp1 = tmp1->next;

    while (tmp2->next != nullptr)
      tmp2 = tmp2->next;

    tmp2->next = tmp1;
  }

  bool detectLoop() {
    Node* fastRunner = head;
    Node* slowRunner = head;

    while (fastRunner != nullptr && fastRunner->next != nullptr) {
      slowRunner = slowRunner->next;
      fastRunner = fastRunner->next->next;
      if (slowRunner == fastRunner) // 충돌 발생
        break;
    }

    if (fastRunner == nullptr || fastRunner->next == nullptr)
      return false;   // 한 번도 만나지 않는다 = 루프가 존재하지 않는다

    fastRunner = head;
    while (fastRunner != slowRunner) {
      slowRunner = slowRunner->next;
      fastRunner = fastRunner->next;
    }

    cout << "루프 시작 지점의 데이터: " << fastRunner->data << endl;
    return true;
  }

};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  FindBeginning* my = new FindBeginning();

  int cntNodes;
  cout << "링크드리스트를 이룰 노드의 개수: ";
  cin >> cntNodes;

  cout << cntNodes << "개의 노드를 공백으로 구분하여 입력해주세요: ";
  int data;
  while (cntNodes--) {
    cin >> data;
    my->addNode(data);
  }

  cout << "루프 시작 지점의 인덱스: ";
  int idxBeginLoop;
  cin >> idxBeginLoop;

  my->makeLoop(idxBeginLoop);

  if (!(my->detectLoop()))
    cout << "루프가 존재하지 않습니다." << endl;

  return 0;
}
