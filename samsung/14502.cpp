#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector < pair<int, int>>;
using vvi = vector<vector<int>>;
using tiii = tuple<int, int, int>;

#define INF 0x3f3f3f3f
#define MAX 10

#define WALL 1
#define VIRUS 2

int board[MAX][MAX];
bool visited[MAX][MAX];
int N, M;
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
int answer = -1;
vii coordi;
int len;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			if (!board[i][j])
				coordi.push_back({i,j});
		}
	}
}

bool is_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < M;;
}

void bfs(int sx, int sy) {
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
			if (!is_range(nx, ny) ||visited[nx][ny]|| board[nx][ny] == WALL)
				continue;
			visited[nx][ny] = true;
			qu.push({ nx,ny });
		}
	}
}

int get_ans() {
	memset(visited, false, sizeof(visited));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == VIRUS&&!visited[i][j])
				bfs(i, j);
		}
	}

	/*
	cout << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << visited[i][j] << " ";
		}
		cout << '\n';
	}
	*/
	int subAns = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if(!visited[i][j]&&board[i][j]==0)
				subAns++;
		}
	}
	return subAns;
}

void print() {
	cout << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << board[i][j] << " ";
		}
		cout << '\n';
	}
}

void dfs(int idx,int cnt) {
	if (cnt == 3) {
		answer = max(answer, get_ans());
		return;
	}
	for (int i = idx; i < len; i++) {
		pii p = coordi[i];
		board[p.first][p.second] = WALL;
		dfs(i + 1, cnt + 1);
		board[p.first][p.second] = 0;
	}
}


void solve() {
	len = (int)coordi.size();
	dfs(0,0);
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}