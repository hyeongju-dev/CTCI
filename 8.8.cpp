#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

void findPermutations(string curr, unordered_map<char, int> m, vector<string>& res, int n) {
  int currLen = curr.size();
	if (n == currLen) {
		res.push_back(curr);
		return;
	}

	for (unordered_map<char,int>::iterator it = m.begin(); it != m.end(); ++it) {
		if (i->second != 0) {
			char c = i->first;
			string f = curr+c;
			i->second--;
			findPermutations(f, m, res, n);
			i->second++;
		}
	}
}

int main() {
	string s = "abbc";
	string curr = "";
	unordered_map<char, int> m;
	int n = s.size();
	for (int i = 0; i < n; ++i) {
		if (m.find(s[i]) != m.end())
			m.find(s[i])->second++;
		else
			m.insert({s[i], 1});
	}
	vector<string> res;
	findPermutations(curr, m, res, n);
	for (int i = 0; i < res.size(); ++i)
		cout << res[i] << endl;
	return 0;
}
