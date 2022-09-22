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

int n, m;
int board[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}
}

int bfs(int sx, int sy) {
	queue<pair<int, int>> qu;
	visited[sx][sy] = true;
	qu.push({ sx,sy });
	int cnt = 1;
	while (!qu.empty()) {
		int x = qu.front().first;
		int y = qu.front().second;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (visited[nx][ny] || !board[nx][ny])
				continue;
			qu.push({ nx,ny });
			visited[nx][ny] = true;
			cnt++;
		}
	}
	return cnt;
}

void solve() {
	int answer = 0;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j]||!board[i][j])
				continue;
			cnt++;
			answer = bfs(i, j);
		}
	}
	cout << cnt << '\n' << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}