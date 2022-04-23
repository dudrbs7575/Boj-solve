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

#define INF 0x3f3f3f3f
#define MAX 21

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vii = vector<pair<int, int>>;

int board[MAX][MAX];
bool visited[MAX][MAX];
int N, M;
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
int answer;

//일반, 검은색, 무지개 검은색은 -1 무지개는 0
//그룹에 무지개 블록 갯수 상관x, 일반 블록은 적어도 1개 존재 + 모든 색 같아야함
//그룹에 속한 블록의 개수는 2보다 커야 함.
//기준 블록은 행의 번호가 가장작고 열의 번호가 가장 작은 블록.
void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); 
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) 
			cin >> board[i][j];
	}
}

bool is_range(int x,int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

pii bfs(int sx, int sy) {
	int blockColor = board[sx][sy];
	int rainbowBlock = 0;
	vii rainbowStore;
	int cnt = 1;
	queue<pii> qu;
	visited[sx][sy] = true;
	qu.push({ sx,sy });
	while (!qu.empty()) {
		int x = qu.front().first;
		int y = qu.front().second;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!is_range(nx, ny)||visited[nx][ny])
				continue;
			if (!(board[nx][ny] == blockColor || board[nx][ny] == 0))
				continue;
			if (board[nx][ny] == 0) {
				rainbowStore.push_back({ nx,ny });
				rainbowBlock++;
			}
			qu.push({ nx,ny });
			visited[nx][ny] = true;
			cnt++;
		}
	}
	for (int i = 0; i < rainbowStore.size(); i++) 
		visited[rainbowStore[i].first][rainbowStore[i].second] = false;
	
	
	if (cnt == 1)
		return { -1,-1 };
	return {cnt,rainbowBlock};
}

pii find_block() {
	memset(visited, false, sizeof(visited));
	int maxCnt = 0;
	int rainbowCnt = 0;
	int standardX = -1;
	int standardY = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j]&&board[i][j]>=1) {
				pii c = bfs(i, j);
				if (maxCnt < c.first) {
					maxCnt = c.first;
					rainbowCnt = c.second;
					standardX = i;
					standardY = j;
				}
				else if (maxCnt == c.first) {
					if (rainbowCnt <= c.second) {
						rainbowCnt = c.second;
						standardX = i;
						standardY = j;
					}
				}
			}
		}
	}
	if (maxCnt == 0)
		return{ -1,-1 };
	return { standardX, standardY };
}

void erase_block(int sx, int sy) {
	memset(visited, false, sizeof(visited));
	int blockColor = board[sx][sy];
	int cnt = 1;
	queue<pii> qu;
	qu.push({ sx,sy });
	visited[sx][sy] = true;
	board[sx][sy] = -2;
	while (!qu.empty()) {
		int x = qu.front().first;
		int y = qu.front().second;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!is_range(nx, ny) || visited[nx][ny])
				continue;
			if (board[nx][ny] != blockColor && board[nx][ny] != 0)
				continue;
			qu.push({ nx,ny });
			board[nx][ny] = -2;
			visited[nx][ny] = true;
			cnt++;
		}
	}
	answer += cnt * cnt;
}

void board_gravity() {
	for (int j = 0; j < N; j++) {
		for (int i = N - 1; i >= 0; i--) {
			if (board[i][j] == -2) {
				int tmpI = i;
				while (tmpI > 0 && board[tmpI][j] == -2) {
					tmpI--;
				}
				if (board[tmpI][j] == -1)
					continue;
				board[i][j] = board[tmpI][j];
				board[tmpI][j] = -2;
			}
		}
	}
}

void rounding() {
	vvi tmp;
	for (int i = 0; i < N; i++) {
		vi ttmp;
		for (int j = 0; j < N; j++) {
			ttmp.push_back(board[i][j]);
		}
		tmp.push_back(ttmp);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = tmp[j][(N - 1 - i)];
		}
	}
}

void solve() {
	while (true) {
		pii standardBlock = find_block();
		if (standardBlock.first == -1 && standardBlock.second == -1)
			break;
		cout << standardBlock.first << "," << standardBlock.second << '\n';
		erase_block(standardBlock.first, standardBlock.second);
		board_gravity();
		rounding();
		board_gravity();
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
