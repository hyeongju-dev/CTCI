#include <iostream>
#include <vector>
using namespace std;

const int GRID_SIZE = 8;
bool checkValid(vector<int>& columns, int row1, int column1);

void placeQueens(int row, vector<int>& columns, vector<vector<int> >& results) {
  if (row == GRID_SIZE) {
    results.push_back(columns);
  } else {
    for (int col = 0; col < GRID_SIZE; ++col) {
      if (checkValid(columns, row, col)) {
        columns[row] = col;
        placeQueens(row+1, columns, results);
      }
    }
  }
}

bool checkValid(vector<int>& columns, int row1, int column1) {
  for (int row2 = 0; row2 < row1; ++row2) {
    int column2 = columns[row2];
    if (column1 == column2)
      return false;

    int columnDistance = abs(column2 - column1);
    int rowDistance = row1 - row2;
    if (columnDistance == rowDistance)
      return false;
  }

  return true;
}
