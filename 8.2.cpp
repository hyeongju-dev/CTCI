#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct Point {
    int row;
    int column;
    Point(int r, int c) : row(r), column(c) {}
};

bool getPath(int** matrix, int currRow, int currColumn, vector<Point*>& path, unordered_set<Point*>& duplicateVisits) {
    if (currRow < 0 || currColumn < 0 || !matrix[currRow][currColumn])
        return false;
    Point* currPos = new Point(currRow, currColumn);

    if (duplicateVisits.find(currPos) != duplicateVisits.end())
        return false;

    bool atOrigin = (currRow==0 && currColumn==0);

    if (atOrigin || getPath(matrix, currRow-1, currColumn, path, duplicateVisits) || getPath(matrix, currRow, currColumn-1, path, duplicateVisits)){
        path.push_back(currPos);
        return true;
    }

    duplicateVisits.insert(currPos);

    return false;
}

vector<Point*> getPath(int** matrix, int rows, int columns) {
    vector<Point*> path;
    unordered_set<Point*> duplicateVisits;

    if (rows!=0 || matrix!=nullptr)
        if (getPath(matrix, rows-1, columns-1, path, duplicateVisits))
            return path;

    return path;
}

int** createMatrix(int rows, int columns) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i)
        matrix[i] = new int[columns];

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            matrix[i][j] = 1;

    return matrix;
}

int main() {
    int** matrix = createMatrix(5, 7);
    matrix[1][3] = -1; matrix[2][5] = -1; matrix[3][2] = -1; matrix[0][1] = -1;

    vector<Point*> path = getPath(matrix, 5, 7);
    if (path.size() == 0)
        cerr << "Path does not exist!" << endl;
    else
        for (int i = 0; i < path.size(); ++i)
            cout << "[" << path[i]->row << "]" << "[" << path[i]->column << "]" << endl;

    return 0;
}
