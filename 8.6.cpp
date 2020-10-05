#include <stack>
#include <iostream>
#include <vector>
using namespace std;

class Tower {
private:
  stack<int> disks;
  int index;

public:
  Tower(int i) { index = i; }

  void add(int d) {
    if (!disks.empty() && disks.top() <= d)
      cout << "Error placing disk " << d << endl;
    else
      disks.push(d);
  }

  void moveTopTo(Tower* t) {
    int top = disks.top(); disks.pop();
    t->add(top);
  }

  void moveDisks(int n, Tower* destination, Tower* buffer) {
    if (n > 0) {
      moveDisks(n-1, buffer, destination);
      moveTopTo(destination);
      buffer->moveDisks(n-1, destination, this);
    }
  }
};

int main() {
  int n = 3;
  vector<Tower*> towers(n);
  for (int i = 0; i < 3; ++i)
    towers[i] = new Tower(i);

  for (int i = n-1; i >= 0; --i)
    towers[0]->add(i);

  towers[0]->moveDisks(n, towers[2], towers[1]);

  return 0;
}
