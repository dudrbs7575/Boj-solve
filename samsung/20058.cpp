#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <tuple>
#include <sstream>
#include <queue>

using namespace std;

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vii = vector<pair<int, int>>;

#define INF 0x3f3f3f3f
#define MAX 100

int N, Q;
int len;
int board[MAX][MAX];
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
bool visited[MAX][MAX];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> Q;
	len = pow(2, N);
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			cin >> board[i][j];
		}
	}
}

bool is_range(int x, int y) {
	return 1 <= x && x <= len && 1 <= y && y <= len;
}

void remove_ice() {
	int tmp[MAX][MAX];
	memset(tmp, 0, sizeof(tmp));
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (!is_range(nx, ny))
					continue;
				if (board[nx][ny] >= 1)
					cnt++;
			}
			if (cnt <= 2) {
				tmp[i][j] -= 1;
			}
		}
	}

	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			board[i][j] += tmp[i][j];
			if (board[i][j] < 0)
				board[i][j] = 0;
		}
	}
}

void select_range(int x, int y, int l) {
	vi tmp;
	vvi v;
	v.resize(l);
	int cnt = 0;
	for (int i = x; i < x + l; i++) {
		for (int j = y; j < y + l; j++) {
			tmp.push_back(board[i][j]);
		}
		v[cnt++] = tmp;
		tmp.clear();
	}
	
	int sx = l-1;
	int sy = 0;
	for (int i = x; i < x + l; i++) {
		int tmpX = sx;
		int tmpY = sy + (i - x);
		for (int j = y; j < y + l; j++){
			board[i][j] = v[tmpX--][tmpY];
		}
	}
}

void rounding(int L) {
	int subLen = pow(2, L);
	for (int i = 1; i <= len; i+=subLen) {
		for (int j = 1; j <= len; j += subLen) {
			select_range(i, j, subLen);
		}
	}
}

int bfs(int sx, int sy) {
	int cnt = 1;
	queue<pii> qu;
	qu.push({ sx,sy });
	visited[sx][sy] = true;
	while (!qu.empty()) {
		int x = qu.front().first;
		int y = qu.front().second;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!is_range(nx, ny)||visited[nx][ny]||board[nx][ny]==0)
				continue;
			qu.push({ nx,ny });
			visited[nx][ny] = true;
			cnt++;
		}
	}
	return cnt;
}

void solve() {
	int level;
	while (Q--) {
		cin >> level;
		rounding(level);
		cout << '\n';
		for (int i = 1; i <= len; i++) {
			for (int j = 1; j <= len; j++) {
				cout << board[i][j];
			}
			cout << '\n';
		}
		remove_ice();
	}
	
	int allIce = 0;
	int maxIce = -1;
	
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			allIce += board[i][j];
		}
	}
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			if (visited[i][j]||board[i][j]==0)
				continue;
			maxIce = max(maxIce, bfs(i, j));
		}
	}
	cout << allIce<<'\n';
	cout << maxIce << '\n';
	
}

int main() {
	init();
	solve();
	return 0;
}
