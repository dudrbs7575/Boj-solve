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

int N, K;
vector<pii> coordi;
int board[1'000][1'000];
int dx[] = { -1,0,1,0 }; //╩С ©Л го аб
int dy[] = { 0,1,0,-1 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;
}

void solve() {
	coordi.push_back({ -1,-1 });
	int val = 1;
	int x = N / 2;
	int y = N / 2;
	board[x][y] = val;
	coordi.push_back({ x,y });
	int dir = 0;
	int cnt = 0;
	int len = 1;
	bool flag = false;
	while (true) {
		for (int i = 0; i < len; i++) {
			x += dx[dir];
			y += dy[dir];
			board[x][y] = ++val;
			coordi.push_back({ x,y });
			if (x == 0 && y == 0) {
				flag = true;
				break;
			}
		}
		if (flag)
			break;
		cnt++;
		dir++;
		if (cnt == 2) {
			cnt = 0;
			len++;
		}
		if (dir == 4)
			dir = 0;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << '\n';
	}
	cout << coordi[K].first+1 << " " << coordi[K].second+1 << '\n';
}

int main() {
	init();
	solve();
	return 0;
}