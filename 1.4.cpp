#include <string>
#include <iostream>
using namespace std;

int getCharIndex(char c) {
    int idx = -1;
    if (c >= 'a' && c <= 'z')
        idx = c - 'a';
    else if (c >= 'A' && c <= 'Z')
        idx = c - 'A';
    return idx;
}

void countFrequency(const string & str, int *frequency) {
    int idx;
    for (const char & c : str) {
        idx = getCharIndex(c);
        if (idx != -1)
            ++frequency[idx];
    }
}

bool checkMaxOneOdd(int *frequency) {
		bool oddAppeared = false;
		for (int i=0; i<26; ++i) {
				if (frequency[i]%2 && oddAppeared)
						return false;
				else if (frequency[i]%2 && !oddAppeared)
						oddAppeared = true;
		}
		return true;
}

bool isPermutationOfPallindrome1(const string & str) {
    int frequency[26] = {0};
    countFrequency(str, frequency);
		return checkMaxOneOdd(frequency);
}


bool isPermutationOfPallindrome2(const string & str) {
    int oddCount = 0;
    int frequency[26] = {0};
    int idx = 0;
    for (const char & c : str) {
        idx = getCharIndex(c);
        if (idx != -1) {
            ++frequency[idx];
            if (frequency[idx] % 2)
                ++oddCount;
            else
                --oddCount;
        }
    }
    return (oddCount <= 1);
}


int toggle(int bitVector, int index) {
    if (index < 0) return bitVector;
    int mask = 1 << index;
    if ((bitVector & mask) == 0)
        bitVector |= mask;
    else
        bitVector &= ~mask;
    return bitVector;
}

bool isExactlyOneBitSet(int bitVector) {
    return ((bitVector & (bitVector - 1)) == 0);
}

bool isPermutationOfPallindrome3(const string & str) {
		int bitVector = 0;
    int id = 0;
    for (const char & c : str) {
        id = getCharIndex(c);
        bitVector = toggle(bitVector, id);
    }
    return (bitVector == 0 || isExactlyOneBitSet(bitVector));
}


int main() {
    string str("Tact Coa");
    cout << "Does \"" << str << "\"  has a string whose permutation is a pallindrome? "
              << "( 1 for true, 0 for false ) : ";
    cout << "Approach 1:" << isPermutationOfPallindrome1( str ) << endl;
    cout << "Approach 2:" << isPermutationOfPallindrome2( str ) << endl;
    cout << "Approach 3:" << isPermutationOfPallindrome3( str ) << endl;


    string str1("A big Cat");
    cout << "Does \"" << str1 << "\" has a string whose permutation is a pallindrome? "
              << "( 1 for true, 0 for false ) : ";
    cout << "Approach 1:" << isPermutationOfPallindrome1( str1 ) << endl;
    cout << "Approach 2:" << isPermutationOfPallindrome2( str1 ) << endl;
    cout << "Approach 3:" << isPermutationOfPallindrome3( str1 ) << endl;


    string str2("Aba cbc");
    cout << "Does \"" << str2 << "\" has a string whose permutation is a pallindrome? "
              << "( 1 for true, 0 for false ) : ";
    cout << "Approach 1:" << isPermutationOfPallindrome1( str2 ) << endl;
    cout << "Approach 2:" << isPermutationOfPallindrome2( str2 ) << endl;
    cout << "Approach 3:" << isPermutationOfPallindrome3( str2 ) << endl;
    return 0;
}
