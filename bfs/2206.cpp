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

#define ll long long
#define vvii vector<vector<pair<int,int>>>
#define vvi vector<vector<int>>
#define vii vector<pair<int,int>>
#define vi vector<int>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
#define MAX 1010

int N, M;
char board[MAX][MAX];
int dist[MAX][MAX][2];
bool visited[MAX][MAX][2];
int dx[] = { 1,0,0,-1 };
int dy[] = { 0,1,-1,0 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < s.length(); j++) {
			board[i][j] = s[j];
		}
	}
}

bool isRange(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < M;
}

int bfs(int sx, int sy) {
	queue<tuple<int, int, int>> qu;
	qu.push({ sx,sy,1 });
	dist[sx][sy][1] = 1;
	visited[sx][sy][1] = true;
	while (!qu.empty()) {
		auto t = qu.front();
		qu.pop();
		int x = get<0>(t);
		int y = get<1>(t);
		int breaking = get<2>(t);
		if (x == N - 1 && y == M - 1) {
			return dist[x][y][breaking];
		}
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!isRange(nx, ny)||visited[nx][ny][breaking])
				continue;
			if (board[nx][ny] == '1') {
				if (breaking) {
					qu.push({ nx,ny,0 });
					dist[nx][ny][0] = dist[x][y][breaking] + 1;
					visited[nx][ny][0] = true;
				}
			}
			else {
				qu.push({ nx,ny,breaking });
				dist[nx][ny][breaking] = dist[x][y][breaking] + 1;
				visited[nx][ny][breaking] = true;
			}
		}
	}
	return -1;
}

void solve() {
	int ans = bfs(0, 0);
	cout << ans << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
