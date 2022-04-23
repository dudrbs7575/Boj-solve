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
using vii = vector<vector<int>>;

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

int bfs(int sx, int sy) {
	int blockColor = board[sx][sy];
	int rainbowBlock = 0;
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
			if (board[nx][ny] != blockColor && board[nx][ny] != 0)
				continue;
			qu.push({ nx,ny });
			visited[nx][ny] = true;
			cnt++;
		}
	}
	return cnt;
}

pii find_block() {
	int maxCnt = -1;
	int standardX;
	int standardY;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j]) {
				int cnt = bfs(i, j);
				if (maxCnt < cnt) {
					maxCnt = cnt;
					standardX = i;
					standardY = j;
				}
			}
		}
	}
	return { standardX, standardY };
}

int erase_block(int sx, int sy) {
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
		cout << x << "," << y << '\n';
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
	return cnt;
}

void solve() {
	pii standardBlock = find_block();
	int eraseNum = erase_block(standardBlock.first, standardBlock.second);
	answer += eraseNum * eraseNum;
	cout << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}
