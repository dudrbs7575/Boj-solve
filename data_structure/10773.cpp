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

int K;
stack<int> st;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> K;
}

void solve() {
	int val;
	while (K--) {
		cin >> val;
		if (!val)
			st.pop();
		else
			st.push(val);
	}
	
	int answer = 0;
	while (!st.empty()) {
		answer += st.top();
		st.pop();
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}