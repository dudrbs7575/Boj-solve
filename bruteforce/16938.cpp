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

using namespace std;
using pii = pair<int, int>;

#define MAX 16
#define INF 0x3f3f3f3f

int N, L, R, X;	// 문제 갯수, 최소 값, 최대 값, 난이도 차이
vector<int> v;
vector<bool> visited;
int answer = 0;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> L >> R >> X;
	visited.resize(N);
	int k;
	for (int i = 0; i < N; i++) {
		cin >> k;
		v.push_back(k);
	}
}

bool is_valid() {
	int sumDifficulty = 0;
	int maxDifficulty = -1;
	int minDifficulty = INF;
	for (int i = 0; i < N; i++) {
		if (visited[i]) {
			sumDifficulty += v[i];
			maxDifficulty = max(maxDifficulty, v[i]);
			minDifficulty = min(minDifficulty, v[i]);
		}
	}
	if (L <= sumDifficulty && sumDifficulty <= R && X <= (maxDifficulty - minDifficulty))
		return true;
	return false;
}

void dfs(int idx, int cnt) {
	if (cnt >= 2) {
		if (is_valid())
			answer++;
	}
	for (int i = idx; i < N; i++) {
		visited[i] = true;
		dfs(i + 1, cnt + 1);
		visited[i] = false;
	}
}

void solve() {
	dfs(0, 0);
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}