#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <tuple>

using namespace std;

#define vvi vector<vector<int>>
#define MAX 100001

int N, M;
vvi tree;
int commendation[MAX];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	tree.resize(N + 1);
	int parent;
	for (int i = 1; i <= N; i++) {
		cin >> parent;
		if (parent == -1)
			continue;
		tree[parent].push_back(i);
	}
	int a, b;
	for (int i = 1; i <= M; i++) {
		cin >> a >> b;
		commendation[a] += b;
	}
}

void dfs(int curNode, int prevNode) {
	commendation[curNode] += commendation[prevNode];
	for (int i = 0; i < tree[curNode].size(); i++) {
		int next = tree[curNode][i];
		dfs(next, curNode);
	}
}

void solve() {
	dfs(1,1);
	for (int i = 1; i <= N; i++)
		cout << commendation[i] << " ";
}

int main() {
	init();
	solve();
	return 0;
}