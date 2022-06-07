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

#define MAX 303

int N, M;
int board[MAX][MAX];
int tmpBoard[MAX][MAX];
bool chk[MAX][MAX];
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

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

bool is_all_melting() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] > 0)
				return false;
		}
	}
	return true;
}

bool is_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < M;
}

void bfs(int sx, int sy) {
	queue<pii> qu;
	chk[sx][sy] = true;
	qu.push({ sx,sy });
	while (!qu.empty()) {
		int x = qu.front().first;
		int y = qu.front().second;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!is_range(nx,ny)||chk[nx][ny] || !board[nx][ny])
				continue;
			qu.push({ nx,ny });
			chk[nx][ny] = true;
		}
	}
}

int get_iceberg_num() {
	int num = 0;
	memset(chk, false, sizeof(chk));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (chk[i][j] || !board[i][j])
				continue;
			num++;
			bfs(i, j);
		}
	}
	return num;
}

void ice_melting() {
	memset(tmpBoard, 0, sizeof(tmpBoard));
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < M - 1; j++) {
			if (!board[i][j])
				continue;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				if (!board[i + dx[k]][j + dy[k]])
					cnt++;
			}
			tmpBoard[i][j] -= cnt;
		}
	}
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < M - 1; j++) {
			board[i][j] + tmpBoard[i][j] > 0 ? board[i][j] += tmpBoard[i][j] : board[i][j] = 0;
		}
	}
}

void solve() {
	int answer = 0;
	bool flag = false;
	while (true) {
		if (is_all_melting()) {
			flag = true;
			break;
		}
		if (get_iceberg_num() >= 2)
			break;
		ice_melting();
		answer++;
	}
	flag ? cout << 0 << '\n' : cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}