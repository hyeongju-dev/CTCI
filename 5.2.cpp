#include <iostream>
#include <string>
using namespace std;

void printBinary(float num) {
  if (num >= 1 || num <= 0) {
    cout << "ERROR" << endl;
    return;
  }

  string binary = "0.";
  while (num > 0) {
    if (binary.size() >= 32) {
      cout << "ERROR" << endl;
      return;
    }

    float r = num * 2;
    if (r >= 1) {
      binary += "1";
      num = r - 1;
    } else {
      binary += "0";
      num = r;
    }
  }

  cout << binary << endl;
}
