#include <iostream>
using namespace std;

enum Color { Red, Yellow, Blue, Green };

bool paintFill(Color **screen, int n, int m, int y, int x, Color c) {
  if (y < 0 || y >= n || x < 0 || x >= m)
    return false;
	if (screen[y][x] == c)
    return false;
	else {
		screen[y][x] = c;
		paintFill(screen, n, m, y, x-1, c);
		paintFill(screen, n, m, y, x+1, c);
		paintFill(screen, n, m, y-1, x, c);
		paintFill(screen, n, m, y+1, x, c);
	}
	return true;
}

int main() {
	int n, m;
	cin >> n >> m;
	Color **screen = new Color*[n];
	for (int i = 0; i < n; ++i)
		screen[i] = new Color[m];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int t;
			cin >> t;
			screen[i][j] = (Color)t;
	  }
  }

	paintFill(screen, n, m, 1, 2, green);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			cout << screen[i][j] << " ";
		cout << endl;
	}

	return 0;
}
