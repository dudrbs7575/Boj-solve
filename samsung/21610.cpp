#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <string.h>
#include <queue>

using namespace std;

int N, M;
int board[51][51];
bool chkCloud[51][51];
queue<pair<int, int>> cloud;
pair<int, int> dir[9] = { {0,0},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1} };
int diagonalX[] = { -1,-1,1,1 };
int diagonalY[] = { -1,1,1,-1 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
}

bool isRange(int x, int y) {
	return 0 < x && x <= N && 0 < y && y <= N;
}

void waterCopy() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (!chkCloud[i][j])
				continue;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int diaX = i + diagonalX[k];
				int diaY = j + diagonalY[k];
				if (!isRange(diaX, diaY))
					continue;
				if (board[diaX][diaY] == 0)
					continue;
				cnt++;
			}
			board[i][j] += cnt;
		}
	}
}

void moveCloud(int d, int s) {
	while (!cloud.empty()) {
		int x = cloud.front().first;
		int y = cloud.front().second;
		cloud.pop();
		int xDir = dir[d].first;
		int yDir = dir[d].second;
		for (int i = 0; i < s; i++) {
			x += xDir;
			if (x == 0)
				x = N;
			if (x == N + 1)
				x = 1;
			y += yDir;
			if (y == 0)
				y = N;
			if (y == N + 1)
				y = 1;
		}
		chkCloud[x][y] = true;
		board[x][y] += 1;
	}
}

void makeCloud() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (board[i][j] < 2 || chkCloud[i][j])
				continue;
			board[i][j] -= 2;
			cloud.push({ i,j });
		}
	}
}

int getAns() {
	int let = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			let += board[i][j];
		}
	}
	return let;
}

int solve() {
	int d, s;
	cloud.push({ N,1 });
	cloud.push({ N,2 });
	cloud.push({ N - 1,1 });
	cloud.push({ N - 1,2 });
	while(M--) {
		cin >> d >> s;
		moveCloud(d,s);
		waterCopy();
		makeCloud();
		memset(chkCloud, false, sizeof(chkCloud));
	}
	return getAns();
}

int main() {
	init();
	cout << solve();
	return 0;
}