/* This problem sounds a lot like the classic binary search problem.
 * Leaveraging the Pattern Matching approach for generating algorithms, how might we apply binary search here? */
#include <vector>
using namespace std;

int magicFast(vector<int>  v) {
  return magicFast(v, 0, v.size()-1);
}

int magicFast(const vector<int> &v, int row, int high) {
  if (high < row)
    return -1;

  int mid = row + (high-row)/2;  // to avoid overflow. effectively, equals (row+high)/2
  if (v[mid] == mid)
    return mid;
  else if (v[mid] > mid)
    return magicFast(v, row, mid-1);
  else
    return magicFast(v, mid+1, high);
}

/* FOLLOW-UP: What if the elements are not distinct? */
int magicFast_followup(const vector<int> &v, int row, int high) {
  if (high < row)
    return -1;

  int mid = row + (high-row)/2;
  if (v[mid] == mid)
    return mid;

  int left = (mid-1 < v[mid] ? mid-1 : v[mid]);
  int leftValue = magicFast_followup(v, row, left);
  if (leftValue >= 0)
    return leftValue;

  int right = (mid+1 > v[mid] ? mid+1 : v[mid]);
  int rightValue = magicFast_followup(right, high);
  return right;
}
