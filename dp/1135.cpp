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
using ll = long long;

#define INF 0x3f3f3f3f
#define MAX 501

int N;
int dp[55];
vector<vector<int>> tree;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	tree.resize(N);
	int parent;
	for (int i = 0; i < N; i++) {
		cin >> parent;
		if (parent == -1)
			continue;
		tree[parent].push_back(i);
	}
}

int go(int cur) {
	if (!tree[cur].size())
		return 0;

	int& ret = dp[cur];
	if (ret != -1)
		return -1;

	vector<int> v;
	for (int next : tree[cur])
		v.push_back(go(next));
	sort(v.rbegin(), v.rend());

	ret = 0;
	int tmp = 1;
	for (int i = 0; i < v.size(); i++)
		ret = max(ret, v[i] + tmp++);

	return ret;
}

void solve() {
	memset(dp, -1, sizeof(dp));
	cout << go(0) << '\n';
}

int main() {
	init();
	solve();
	return 0;
}