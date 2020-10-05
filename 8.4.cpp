#include <vector>
#include <iostream>
using namespace std;

vector<int> convertIntToSet(int x, const vector<int>& set) {
  vector<int> subset;
  int index = 0;

  for (int k = x; k > 0; k = k >> 1) {
    if ((k & 1) == 1)
      subset.push_back(set[index]);
    index++;
  }

  return subset;
}

vector<vector<int> > getPowerset(const vector<int>& set) {
  vector<vector<int> > powerset;
  int max = 1 << set.size();  // 2^n

  for (int k = 0; k < max; ++k) {
    vector<int> subset = convertIntToSet(k, set);
    powerset.push_back(subset);
  }

  return powerset;
}

int main() {
  vector<int> testset;
  testset.push_back(1); testset.push_back(2); testset.push_back(3); testset.push_back(4);
  
  vector<vector<int> > testPowerset = getPowerset(testset);
  for (int i = 0; i < testPowerset.size(); ++i) {
    for (int j = 0; j < testPowerset[i].size(); ++j)
      cout << testPowerset[i][j] << ' ';
    cout << endl;
  }

  return 0;
}
