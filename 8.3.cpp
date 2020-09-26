#include <vector>
using namespace std;

int magicFast(vector<int>  v) {
  return magicFast(v, 0, v.size()-1);
}

int magicFast(const vector<int> &v, int start, int end) {
  if (end < start)
    return -1;

  int mid = start + (end-start)/2;  // to avoid overflow. effectively, equals (start+end)/2
  if (v[mid] == mid)
    return mid;
  else if (v[mid] > mid)
    return magicFast(v, start, mid-1);
  else
    return magicFast(v, mid+1, end);
}

/* FOLLOW-UP: What if the elements are not distinct? */
int magicFast_followup(const vector<int> &v, int start, int end) {
  if (end < start)
    return -1;

  int mid = start + (end-start)/2;
  if (v[mid] == mid)
    return mid;

  int left = (mid-1 < v[mid] ? mid-1 : v[mid]);
  int leftValue = magicFast(v, start, left);
  if (leftValue >= 0)
    return leftValue;

  int right = (mid+1 > v[mid] ? mid+1 : v[mid]);
  int rightValue = magicFast(right, end);
  return right;
}
