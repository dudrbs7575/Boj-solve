#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using pii = pair<int, int>;
using piii = pair<pair<int, int>, int>;
using tiii = tuple<int, int, int>;
using tiiii = tuple<int, int, int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vii = vector<pair<int, int>>;


#define INF 0x3f3f3f3f
#define MAX 111

int board[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
int N, L, R;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> L >> R;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
}

bool is_range(int x, int y) {
	return 1 <= x && x <= N && 1 <= y && y <= N;
}

int bfs(int sx, int sy) {
	visited[sx][sy] = true;
	queue<pii> qu;
	qu.push({ sx,sy });
	int cnt = 1;
	int civil = board[sx][sy];
	vii coordi;
	coordi.push_back({ sx,sy });
	while (!qu.empty()) {
		int x = qu.front().first;
		int y = qu.front().second;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!is_range(nx, ny) || visited[nx][ny])
				continue;
			if(L>abs(board[x][y]-board[nx][ny])||R<abs(board[x][y]-board[nx][ny]))
				continue;
			cnt++;
			civil += board[nx][ny];
			coordi.push_back({ nx,ny });
			qu.push({ nx,ny });
			visited[nx][ny] = true;
		}
	}
	int resize = civil / cnt;
	for (int i = 0; i < coordi.size(); i++) 
		board[coordi[i].first][coordi[i].second] = resize;
	return cnt;
}

bool can_move_civil() {
	int flag = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j])
				continue;
			flag=max(flag, bfs(i, j));
		}
	}
	if (flag == 1)
		return false;
	return true;
}

void solve() {
	int answer = 0;
	while (true) {
		memset(visited, 0, sizeof(visited));
		if (!can_move_civil())
			break;
		answer++;
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
