#include <iostream>
#include <vector>
using namespace std;

const int DENOMS_SIZE = 4;
int makeChange(int amount, const int* denoms, int index, vector<vector<int> >& map);

int makeChange(int n) {
  const int denoms[] = {25, 10, 5, 1};
  vector<vector<int> > map(n+1, vector<int>(DENOMS_SIZE, 0));
  return makeChange(n, denoms, 0, map);
}

int makeChange(int amount, const int denoms[4], int index, vector<vector<int> >& map) {
  if (map[amount][index] > 0)
    return map[amount][index];
  if (index >= DENOMS_SIZE-1)
    return 1;
  int denomAmount = denoms[index];
  int ways = 0;
  for (int i = 0; i * denomAmount <= amount; ++i) {
    int amountRemaining = amount - i * denomAmount;
    ways += makeChange(amountRemaining, denoms, index+1, map);
  }
  map[amount][index] = ways;
  return ways;
}

int main() {
  cout << makeChange(10) << endl;

	return 0;
}
