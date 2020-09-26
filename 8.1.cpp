#include <vector>
using namespace std;

int countWays(int n) {
  vector<int> cache(n, -1);
  return countWays(n, cache);
}

int countWays_Recursive(int n, vector<int> &cache) {
  if (n < 0) {
    return 0;
  } else if (n == 0) {
    return 1;
  } else if (cache[n] > -1) {
    return cache[n];
  } else {
    cache[n] = countWays(n-1, cache) + countWays(n-2, cache) + countWays(n-3, cache);
    return cache[n];
  }
}

int countWays_Iterative(int n, vector<int> &cache) {
  cache[1] = 1; cache[2] = 2; cache[3] = 4;
  for (int i = 4; i <= n; ++i)
    cache[i] = cache[i-1] + cache[i-2] + cache[i-3];
  return cache[n];
}
