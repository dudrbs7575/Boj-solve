#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	stack<pair<char,int>> st;
	string s;
	cin >> s;

	int left = 0;
	int right = 0;
	int sum = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			left++;
			sum++;
		}
		else {
			right++;
			sum--;
		}

		if (sum == 0) 
			left = 0;
		
		if (sum < 0) {
			cout << right << '\n';
			return 0;
		}
	}
	cout << left << '\n';
	return 0;
}