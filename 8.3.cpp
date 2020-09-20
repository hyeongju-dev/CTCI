#include <vector>
using namespace std;

int magicFast(vector<int> v) {
  return magicFast(v, 0, v.size()-1);
}

int magicFast(vector<int> &v, int start, int end) {
  if (end<start)
    return -1;

  int mid = start+(end-start)/2;
  if (v[mid] == mid)
    return mid;
  else if (v[mid] > mid)
    return magicFast(v, start, mid-1);
  else
    return magicFast(v, mid+1, end);
}
