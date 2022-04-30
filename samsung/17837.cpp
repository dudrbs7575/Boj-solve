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
#define MAX 15

#define WHITE 0
#define RED 1
#define BLUE 2
//흰색인 경우 모든 말 차례대로 쌓인 상태.
//빨간색인 경우 빨간칸에 있는 말 순서 바꾸기X 빨간색으로 이동하는 말만 역순해서 쌓기
//파란색인 경우 이동하지 않고 이동방향 반대로 바꾸고 한칸 이동. 만약 반대도 파란색이다? 멈춰있기.
//체스판을 벗어날때도 이동방향 바꾸고 한칸 이동. 만약 반대가 파란색이다? 멈춰있기.

int board[MAX][MAX];
vi info[MAX][MAX];
vector<tuple<int,int,int,int>> coordi;
int dx[] = { 0,0,0,-1,1};
int dy[] = { 0,1,-1,0,0 };
int N, K;
bool flag = false;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
	int x, y, d;
	for (int i = 1; i <= K; i++) {
		cin >> x >> y >> d;
		info[x][y].push_back({ i });
		coordi.push_back({ i,d,x,y });
	}
}

void print() {
	cout << '\n';
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << info[i][j].size() << " ";
		}
		cout << '\n';
	}
}

bool is_range(int x, int y) {
	return 1 <= x && x <= N && 1 <= y && y <= N;
}

bool is_answer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (info[i][j].size() >= 4)
				return true;
		}
	}
	return false;
}

int change_direction(int d) {
	if (d == 1)
		d = 2;
	else if (d == 2)
		d = 1;
	else if (d == 3)
		d = 4;
	else
		d = 3;
	return d;
}

int find_idx(int x,int y,int num) {
	for (int i = 0; i < info[x][y].size(); i++) {
		if (info[x][y][i] == num)
			return i;
	}
}

void move_chess() {
	for (int i = 0; i < coordi.size();i++) {
		int num = get<0>(coordi[i]);
		int d = get<1>(coordi[i]);
		int x = get<2>(coordi[i]);
		int y = get<3>(coordi[i]);
		int nx = x + dx[d]; int ny = y + dy[d];
		if (!is_range(nx, ny) || board[nx][ny] == BLUE) {
			d = change_direction(d);
			coordi[i] = { num,d,x,y };
			nx = x + dx[d]; ny = y + dy[d];
			if (!is_range(nx, ny) || board[nx][ny] == BLUE)
				continue;
			else {
				if (board[nx][ny] == WHITE) {
					int idx = find_idx(x, y, num);
					vi tmp;
					for (int j = idx; j < info[x][y].size(); j++) {
						info[nx][ny].push_back(info[x][y][j]);
						coordi[info[x][y][j] - 1] = { info[x][y][j],get<1>(coordi[info[x][y][j]-1]),nx,ny };
					}
					for (int j = 0; j < idx; j++)
						tmp.push_back(info[x][y][j]);
					info[x][y].clear();
					info[x][y] = tmp;
				}
				else if(board[nx][ny]==RED) {
					int idx = find_idx(x, y, num);
					vi tmp;
					for (int j = info[x][y].size() - 1; j >= idx; j--) {
						info[nx][ny].push_back(info[x][y][j]);
						coordi[info[x][y][j] - 1] = { info[x][y][j],get<1>(coordi[info[x][y][j]-1]),nx,ny };
					}
					for (int j = 0; j < idx; j++)
						tmp.push_back(info[x][y][j]);
					info[x][y].clear();
					info[x][y] = tmp;
				}
			}
			continue;
		}
		
		if (board[nx][ny] == WHITE) {
			int idx = find_idx(x, y, num);
			vi tmp;
			for (int j=idx; j < info[x][y].size(); j++) {
				info[nx][ny].push_back(info[x][y][j]);
				coordi[info[x][y][j]-1] = { info[x][y][j],get<1>(coordi[info[x][y][j]-1]),nx,ny};
			}
			for (int j = 0; j < idx; j++)
				tmp.push_back(info[x][y][j]);
			info[x][y].clear();
			info[x][y] = tmp;
		}
		else if(board[nx][ny] == RED) {
			int idx = find_idx(x, y, num);
			vi tmp;
			for (int j =info[x][y].size()-1; j >= idx; j--) {
				info[nx][ny].push_back(info[x][y][j]);
				coordi[info[x][y][j]-1] = { info[x][y][j],get<1>(coordi[info[x][y][j]-1]),nx,ny };

			}
			for (int j = 0; j < idx; j++)
				tmp.push_back(info[x][y][j]);
			info[x][y].clear();
			info[x][y] = tmp;
		}
		if (is_answer()) {
			flag = true;
			return;
		}
	}
}

void solve() {
	int answer = 1;
	while (true) {
		move_chess();
		if (answer > 1000 || flag)
			break;
		answer++;
	}
	(answer > 1000) ? cout << -1 << '\n' : cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}