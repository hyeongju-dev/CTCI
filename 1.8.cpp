#include <iostream>
using namespace std;

void nullifyRow(int **matrix, int M, int row) {
	for (int j = 0; j < M; ++j)
		matrix[row][j] = 0;
}

void nullifyCol(int **matrix, int N, int col) {
	for (int i = 0; i < N; ++i)
		matrix[i][col] = 0;
}

void nullifyMatrix(int **matrix, int N, int M) {
  bool rowHasZero = false, colHasZero = false;

  for (int i = 0; i < N; ++i)
    if (matrix[i][0] == 0) {
      colHasZero = true;
      break;
    }

  for (int j = 0; j < M; ++j)
    if (matrix[0][j] == 0) {
      rowHasZero = true;
      break;
    }

  for (int i = 1; i < N; ++i)
    for (int j = 1; j < M; ++j)
      if (matrix[i][j] == 0) {
        matrix[i][0] = 0;
        matrix[0][j] = 0;
      }

  for (int i = 1; i < N; ++i)
    if (matrix[i][0] == 0)
      nullifyRow(matrix, M, i);

  for (int j = 1; j < M; ++j)
    if (matrix[0][j] == 0)
      nullifyColumn(matrix, N, j);

  if (colHasZero)
    nullifyColumn(matrix, N, 0);

  if (rowHasZero)
    nullifyRow(matrix, M, 0);

}


int main() {
	int N, M;
	cout << "Enter number of rows:";
	cin >> N;
	cout << "Enter number of cols:";
	cin >> M;
	int ** matrix = new int*[N];
	for (int i =0; i < N; ++i)
		matrix[i] = new int[M];

	cout << "Provide N x M matrix" << endl;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			cin >> matrix[i][j];

	nullifyMatrix(matrix, N, M);

	return 0;
}
