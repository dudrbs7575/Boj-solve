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

int board[MAX][MAX];
int dp[MAX][MAX];
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}

bool is_valid(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

int go(int i, int j) {
	int& ret = dp[i][j];
	if (ret != -1)
		return ret;

	ret = 1;
	int nx; int ny;
	for (int k = 0; k < 4; k++) {
		nx = i + dx[k];
		ny = j + dy[k];
		if (is_valid(nx, ny) && board[nx][ny] > board[i][j])
			ret = max(ret, go(nx, ny) + 1);
	}
	return ret;
}

void solve() {
	int answer = 0;
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			answer = max(answer, go(i, j));
		}
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}