#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

using pii = pair<int, int>;
using piii = pair<pair<int, int>, int>;
using tiii = tuple<int, int, int>;
using tiiii = tuple<int, int, int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vii = vector<pair<int, int>>;


#define INF 0x3f3f3f3f
#define MAX 22

vector<tiii> heater;
vii coordi;
int board[MAX][MAX];
int tmpBoard[MAX][MAX];
int wall[MAX][MAX][2];
bool chk[MAX][MAX];
int dx[] = {0,0,0,-1,1};	
int dy[] = {0,1,-1,0,0};
int R, C, K, W;


void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> R >> C >> K;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> board[i][j];
			if (!board[i][j])
				continue;
			if (board[i][j] == 5)
				coordi.push_back({ i,j });
			else
				heater.push_back({ i,j,board[i][j] });
			board[i][j] = 0;
		}
	}
	memset(wall, 0, sizeof(wall));
	cin >> W;
	int x, y, t;
	while (W--) {
		cin >> x >> y >> t;
		wall[x][y][t] = 1;
	}
}

bool is_range(int x, int y) {
	return 1 <= x && x <= R && 1 <= y && y <= C;
}

void make_heat() {
	//우 좌 상 하
	for (auto h : heater) {
		memset(chk, false, sizeof(chk));
		queue<pii> qu;
		int sx = get<0>(h);
		int sy = get<1>(h);
		int d = get<2>(h);
		qu.push({ sx + dx[d],sy + dy[d] });
		board[sx + dx[d]][sy + dy[d]] += 5;
		int val = 4;
		while (!qu.empty()) {
			if (val == 0)
				break;
			int qSize = qu.size();
			while (qSize--) {
				int x = qu.front().first;
				int y = qu.front().second;
				qu.pop();
				if (d == 1) {
					if(is_range(x-1,y)&&is_range(x-1,y+1)){
						if (wall[x][y][0] !=1 && wall[x - 1][y][1] != 1) {
							if (!chk[x - 1][y + 1]) {
								board[x - 1][y + 1] += val;
								chk[x - 1][y + 1] = true;
								qu.push({ x - 1,y + 1 });
							}
						}
					}
					if (is_range(x, y + 1)) {
						if (wall[x][y][1] != 1) {
							if (!chk[x][y + 1]) {
								board[x][y + 1] += val;
								chk[x][y + 1] = true;
								qu.push({ x,y + 1 });
							}
						}
					}
					if (is_range(x + 1, y) && is_range(x + 1, y + 1)) {
						if (wall[x+1][y][0] != 1 && wall[x + 1][y][1] != 1) {
							if (!chk[x + 1][y + 1]) {
								board[x + 1][y + 1] += val;
								chk[x + 1][y + 1] = true;
								qu.push({ x + 1,y + 1 });
							}
						}
					}
				}
				else if (d == 2) {
					if (is_range(x - 1, y) && is_range(x - 1, y - 1)) {
						if (wall[x][y][0] != 1 && wall[x - 1][y - 1][1] != 1) {
							if (!chk[x - 1][y - 1]) {
								board[x - 1][y - 1] += val;
								chk[x - 1][y - 1] = true;
								qu.push({ x - 1,y - 1 });
							}
						}
					}
					if (is_range(x, y - 1)) {
						if (wall[x][y - 1][1] != 1) {
							if (!chk[x][y - 1]) {
								board[x][y - 1] += val;
								chk[x][y - 1] = true;
								qu.push({ x,y - 1 });
							}
						}
					}
					if (is_range(x + 1, y) && is_range(x + 1, y - 1)) {
						if (wall[x + 1][y][0] !=1 && wall[x + 1][y - 1][1] != 1) {
							if (!chk[x + 1][y - 1]) {
								board[x + 1][y - 1] += val;
								chk[x + 1][y - 1] = true;
								qu.push({ x + 1,y - 1 });
							}
						}
					}
				}
				else if (d == 3) {
					if (is_range(x, y - 1) && is_range(x - 1, y - 1)) {
						if (wall[x][y - 1][1] != 1 && wall[x][y - 1][0] != 1) {
							if (!chk[x-1][y - 1]) {
								board[x - 1][y - 1] += val;
								chk[x - 1][y - 1] = true;
								qu.push({ x - 1,y - 1 });
							}
						}
					}
					if (is_range(x - 1, y)) {
						if (wall[x][y][0] != 1) {
							if (!chk[x - 1][y]) {
								board[x - 1][y] += val;
								chk[x - 1][y] = true;
								qu.push({ x - 1,y });
							}
						}
					}
					if (is_range(x, y + 1) && is_range(x - 1, y + 1)) {
						if (wall[x][y][1] != 1 && wall[x][y + 1][0] != 1) {
							if (!chk[x - 1][y + 1]) {
								board[x - 1][y + 1] += val;
								chk[x - 1][y + 1] = true;
								qu.push({ x - 1,y + 1 });
							}
						}
					}
				}
				else {
					if (is_range(x, y - 1) && is_range(x + 1, y - 1)) {
						if (wall[x][y - 1][1] != 1 && wall[x + 1][y - 1][0] != 1) {
							if (!chk[x + 1][y - 1]) {
								board[x + 1][y - 1] += val;
								chk[x + 1][y - 1] = true;
								qu.push({ x + 1,y - 1 });
							}
						}
					}
					if (is_range(x + 1, y)) {
						if (wall[x + 1][y][0] != 1) {
							if (!chk[x + 1][y]) {
								board[x + 1][y] += val;
								chk[x + 1][y] = true;
								qu.push({ x + 1,y });
							}
						}
					}
					if (is_range(x, y + 1) && is_range(x + 1, y + 1)) {
						if (wall[x][y][1] != 1 && wall[x + 1][y + 1][0] != 1) {
							if (!chk[x + 1][y + 1]) {
								board[x + 1][y + 1] += val;
								chk[x + 1][y + 1] = true;
								qu.push({ x + 1,y + 1 });
							}
						}
					}
				}
			}
			val--;
		}
	}
}

void minus_heat() {
	for (int i = 1; i <= R; i++) {
		if (board[i][1]>=1)
			board[i][1] -= 1;
		if (board[i][C]>=1)
			board[i][C] -= 1;
	}
	for (int i = 2; i <= C-1; i++) {
		if (board[1][i]>=1)
			board[1][i] -= 1;
		if (board[R][i]>=1)
			board[R][i] -= 1;
	}
}

void resize_heat() {
	//우 좌 상 하
	//t=0 위로 t=1 우로
	memset(tmpBoard, 0, sizeof(tmpBoard));
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			int nx1 = i + dx[1]; int ny1 = j + dy[1];
			int nx2 = i + dx[4]; int ny2 = j + dy[4];
			if (is_range(nx1, ny1)) {
				if (wall[i][j][1] != 1) {
					int t = abs(board[i][j] - board[nx1][ny1])/4;
					if (board[i][j] > board[nx1][ny1]) {
						tmpBoard[i][j] -= t;
						tmpBoard[nx1][ny1] += t;
					}
					else {
						tmpBoard[i][j] += t;
						tmpBoard[nx1][ny1] -= t;
					}
				}
			}
			if (is_range(nx2, ny2)) {
				if (wall[nx2][ny2][0] != 1) {
					int t = abs(board[i][j] - board[nx2][ny2]) / 4;
					if (board[i][j] > board[nx2][ny2]) {
						tmpBoard[i][j] -= t;
						tmpBoard[nx2][ny2] += t;
					}
					else {
						tmpBoard[i][j] += t;
						tmpBoard[nx2][ny2] -= t;
					}
				}
			}
		}
	}
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			board[i][j] += tmpBoard[i][j];
		}
	}
}

bool is_answer() {
	for (int i = 0; i < coordi.size(); i++) {
		if (board[coordi[i].first][coordi[i].second] < K)
			return false;
	}
	return true;
}

void print() {
	cout << '\n';
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << board[i][j] << " ";
		}
		cout << '\n';
	}
}

void solve() {
	int chocolate = 0;
	while (true) {
		make_heat();
		resize_heat();
		minus_heat();
		chocolate++;
		if (chocolate == 101||is_answer())
			break;
	}
	cout << chocolate << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
