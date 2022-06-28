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

#define MAX 100

int board[MAX][MAX];
int mark[MAX][MAX];
bool chk[MAX][MAX];
int N;
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

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

bool is_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

void bfs(int color,int sx, int sy) {
	queue<pair<int, int>> qu;
	qu.push({ sx,sy });
	mark[sx][sy] = color;
	while (!qu.empty()) {
		int x = qu.front().first;
		int y = qu.front().second;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!is_range(nx, ny) || !board[nx][ny]||mark[nx][ny])
				continue;
			mark[nx][ny] = color;
			qu.push({ nx,ny });
		}
	}
}

void print() {
	cout << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << mark[i][j] << " ";
		}
		cout << '\n';
	}
}

void mark_land() {
	int color = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] && !mark[i][j]) {
				bfs(++color,i,j);
			}
		}
	}
}

int get_road(int sx, int sy) {
	memset(chk, false, sizeof(chk));
	queue<pair<pair<int, int>, int>> qu;
	qu.push({ { sx,sy },0 });
	while (!qu.empty()) {
		int x = qu.front().first.first;
		int y = qu.front().first.second;
		int dist = qu.front().second;
		qu.pop();
		if (mark[x][y] && mark[x][y] != mark[sx][sy]) {
			return dist-1;
		}
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!is_range(nx, ny) || mark[sx][sy] == mark[nx][ny]||chk[nx][ny])
				continue;
			chk[nx][ny] = true;
			qu.push({ { nx,ny }, dist+1});
		}
	}
	return 0x3f3f3f3f;
}

int get_ans() {
	int answer = 0x3f3f3f3f;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j]) {
				answer = min(answer, get_road(i, j));
			}
		}
	}
	return answer;
}

void solve() {
	mark_land();
	cout << get_ans() << '\n';
}

int main() {
	init();
	solve();
	return 0;
}