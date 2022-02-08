#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>

using namespace std;

#define A 10001
#define B 501

char board[A][B];
bool visit[A][B];
int R, C;
int dx[] = {-1,0,1};
int dy[] = { 1,1,1 };
int ans;
bool flag;

void init() {
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> board[i][j];
		}
	}
}

void dfs(int x, int y) {
	visit[x][y] = true;
	if (y == C - 1) {
		flag = true;
		ans++;
		return;
	}
	for (int i = 0; i < 3; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx>=0&&ny>=0&&nx<R&&ny<C) {
			if (visit[nx][ny] == false && board[nx][ny] == '.') {
				if (flag == true)
					return;
				dfs(nx, ny);
			}
		}
	}
}

void solve() {
	for (int i = 0; i < R; i++) {
		flag = false;
		dfs(i, 0);
	}
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	init();
	solve();
	return 0;
}
