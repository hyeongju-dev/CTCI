#include <vector>
using namespace std;

int countWays(int n) {
  vector<int> memo(n,-1);
  return countWays(n, memo);
}

int countWays(int n, vector<int> &memo) {
  if (n<1)
    return 0;
  else if (n == 1)
    return 1;
  else if (memo[n] > -1)
    return memo[n];
  else {
    memo[n] = countWays(n-1,memo) + countWays(n-2,memo) + countWays(n-3,memo);
    return memo[n];
  }
}
