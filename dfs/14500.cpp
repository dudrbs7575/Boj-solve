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

#define MAX 555

bool visited[MAX][MAX];
int board[MAX][MAX];
int N, M;
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
int answer = 0;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}

bool is_valid(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < M;
}

void dfs(int x, int y, int sum, int cnt) {
	visited[x][y] = true;
	if (cnt == 3) {
		answer = max(answer, sum);
		return;
	}
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!is_valid(nx,ny)||visited[nx][ny])
			continue;
		dfs(nx, ny, sum + board[nx][ny], cnt + 1);
		visited[nx][ny] = false;
	}
}

void another_shape(int i, int j) {
	if (is_valid(i, j) && is_valid(i, j + 1) && is_valid(i, j + 2) && is_valid(i + 1, j + 1)) {
		answer = max(answer, board[i][j] + board[i][j + 1] + board[i][j + 2] + board[i + 1][j + 1]);
	}
	if (is_valid(i, j) && is_valid(i-1, j) && is_valid(i-2, j) && is_valid(i -1, j + 1)) {
		answer = max(answer, board[i][j] + board[i - 1][j] + board[i - 2][j] + board[i - 1][j + 1]);
	}
	if (is_valid(i, j) && is_valid(i, j + 1) && is_valid(i, j + 2) && is_valid(i - 1, j + 1)) {
		answer = max(answer, board[i][j] + board[i][j + 1] + board[i][j + 2] + board[i - 1][j + 1]);
	}
	if (is_valid(i, j) && is_valid(i-1, j) && is_valid(i-2, j) && is_valid(i-1 , j - 1)) {
		answer = max(answer, board[i][j] + board[i - 1][j] + board[i - 2][j] + board[i - 1][j - 1]);
	}
}

void get_tet_max_point(int i, int j) {
	dfs(i, j,board[i][j], 0);
	another_shape(i,j);
}

void solve() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			memset(visited, false, sizeof(visited));
			get_tet_max_point(i, j);
		}
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}