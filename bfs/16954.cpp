#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <queue>

using namespace std;

vector<vector<char>> board = vector<vector<char>>(8, vector<char>(8, 0));
int dx[] = { 0,0,-1,1,1,1,-1,-1,0 };
int dy[] = { -1,1,0,0,1,-1,1,-1,0 };

void wall_down() {
	vector<char> tmp;
	for (int i = 0; i < 8; i++)
		tmp.push_back('.');
	for (int i = 7; i >= 1; i--) 
		board[i] = board[i - 1];
	board[0] = tmp;

/*
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (tmp[i][j] == '#') {
				board[i][j] = '.';
				if (i == 7)
					continue;
				board[i + 1][j] = '#';
			}
		}
	}
*/
	cout << '\n';
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << board[i][j];
		}
		cout << '\n';
	}
}

bool isRange(int x, int y) {
	return 0 <= x && x < 8 && 0 <= y && y < 8;
}

bool bfs() {
	queue<pair<int, int>> qu;
	qu.push({ 7,0 });
	while (!qu.empty()) {
		int qSize = qu.size();
		while (qSize--) {
			int x = qu.front().first;
			int y = qu.front().second;
			qu.pop();
			cout << x << "," << y << " ";
			if (board[x][y] == '#')
				continue;
			if (x == 0 && y == 7)
				return true;
			for (int i = 0; i < 9; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (!isRange(nx, ny) || board[nx][ny] == '#')
					continue;
				qu.push({ nx,ny });
			}
		}
		cout << '\n';
		wall_down();
	}
	return false;
}

void solve() {
	if (bfs())
		cout << 1 << '\n';
	else
		cout << 0 << '\n';
	return;
}

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> board[i][j];
		}
	}
}

int main() {
	init();
	solve();
	return 0;
}