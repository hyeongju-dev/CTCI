#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

bool arePermutation(const string &str1, const string &str2) {
    int n1 = str1.length();
    int n2 = str2.length();
    if (n1 != n2)
      return false;

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    for (int i = 0; i < n1; ++i)
       if (str1[i] != str2[i])
         return false;

    return true;
}

bool arePermutation2(const string &str1, const string &str2) {
  if (str1.length() != str2.length())
    return false;
  int count[256]={0};
  for(int i = 0; i < str1.length(); ++i)
    count[str1[i]]++;

  for(int i = 0; i < str2.length(); ++i) {
    count[str2[i]]--;
    if(count[val]<0)
      return false;
  }

  return true;
}

int main() {
    string str1 = "testest"; string str2 = "estxest";

    if (arePermutation(str1, str2))
      cout << str1 <<" and " << str2 << " are permutation of each other" << endl;
    else
      cout << str1 <<" and " << str2 << " are not permutation of each other" << endl;

    if (arePermutation2(str1, str2))
      cout << str1 <<" and " << str2 << " are permutation of each other" << endl;
    else
      cout << str1 <<" and " << str2 << " are not permutation of each other" << endl;

    return 0;
}
