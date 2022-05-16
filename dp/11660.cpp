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

#define MAX 1025

int board[MAX][MAX];
int dp[MAX][MAX];
int N, M;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1] + board[i][j] - dp[i - 1][j - 1];
		}
	}
}
void solve() {
	int x1, y1, x2, y2;
	while (M--) {
		cin >> x1 >> y1 >> x2 >> y2;
		cout << dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1] << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}