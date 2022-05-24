#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <set>
#include <queue>
#include <stack>

using namespace std;
using pii = pair<int, int>;

int N;
vector<int> input;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	input.resize(N);
	for (int i = 0; i < N; i++)
		cin >> input[i];
}

void solve() {
	int cur = 0;
	stack<int> st;
	st.push(0);
	bool flag = false;
	vector<char> ans;
	for (int i = 0; i < input.size(); i++) {
		int cmd = input[i];
		if (cmd < st.top()||(cmd>st.top()&&cur>cmd)) {
			flag = true;
			break;
		}
		while (true) {
			if (st.top() == cmd) {
				st.pop();
				ans.push_back('-');
				break;
			}
			cur++;
			st.push(cur);
			ans.push_back('+');
		}
	}
	if (flag)
		cout << "NO" << '\n';
	else {
		for (auto c : ans)
			cout << c << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}