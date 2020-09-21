#include <string>
#include <vector>
#include <iostream>
#include <bitset>
using namespace std;

bool isUniqueChars(const string &str){
		if (str.length() > 256)
			return false;
		vector<bool> char_set(256);
		for (int i = 0; i < str.length(); ++i){
			int val = str[i];
			if (char_set[val])
				return false;
			char_set[val] = true;
		}
		return true;
}

bool isUniqueChars_bitvector(const string &str) {
	bitset<256> bits(0);
	for(int i = 0; i < str.length(); ++i) {
		int val = str[i];
		if(bits.test(val) > 0)
			return false;
		bits.set(val);
	}
	return true;
}

bool isUniqueChars_noDS(const string &str) {
	for(int i = 0; i < str.length()-1; ++i)
		for(int j = i+1; j < str.length(); ++j)
			if(str[i] == str[j])
				return false;
	return true;
}

int main(){
		vector<string> words = {"abcde", "hello", "apple", "kite", "padle"};

		for (auto word : words)
			cout << word << string(": ") << boolalpha << isUniqueChars(word) << endl;
		for (auto word : words)
			cout << word << string(": ") << boolalpha << isUniqueChars_bitvector(word) << endl;
		for (auto word : words)
			cout << word << string(": ") << boolalpha << isUniqueChars_noDS(word) << endl;

		return 0;
}
