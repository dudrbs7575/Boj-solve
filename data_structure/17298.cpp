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

#define MAX 1'000'001

int N;
vector<int> v;
int ans[MAX];
stack<int> st;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	v.resize(N + 1);
	for (int i = 1; i <= N; i++)
		cin >> v[i];
}

void solve() {
	memset(ans, -1, sizeof(ans));
	for (int i = 1; i <= N; i++) {
		while (!st.empty() && v[st.top()] < v[i]) {
			ans[st.top()] = v[i];
			st.pop();
		}
		st.push(i);
	}
	for (int i = 1; i <= N; i++)
		cout << ans[i] << " ";
}

int main() {
	init();
	solve();
	return 0;
}