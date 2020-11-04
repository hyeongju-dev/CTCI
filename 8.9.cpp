#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<string> res;
int n;

void parens(int cntLeft, int cntRight, string curr) {
  if (cntRight == n) {
    res.push_back(curr);
    return;
  }

  if (cntLeft < n)
    parens(cntLeft+1, cntRight, curr+"(");
  if (cntRight < cntLeft)
    parens(cntLeft, cntRight+1, curr+")");
}

int main() {
  n = 3;
  parens(0, 0, "");
  for (string r : res)
    cout << r << endl;

  return 0;
}
