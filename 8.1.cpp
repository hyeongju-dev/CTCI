#include <vector>
using namespace std;

int countWays(int n) {
  vector<int> cache(n,-1);
  return countWays(n, cache);
}

int countWays(int n, vector<int> &cache) {
  if (n < 1) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else if (cache[n] > -1) {
    return cache[n];
  } else {
    cache[n] = countWays(n-1, cache) + countWays(n-2, cache) + countWays(n-3, cache);
    return cache[n];
  }
}
