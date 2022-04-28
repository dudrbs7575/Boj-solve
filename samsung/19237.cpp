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

vii board[MAX][MAX];
pii smell[MAX][MAX];
vi direction[444][5];
//1~4 ╩С го аб ©Л
int dx[] = {0, -1,1,0,0 };
int dy[] = {0, 0,0,-1,1 };
int N, M, K;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> K;
	vector<tiii> shark;
	vi startDirection;
	startDirection.resize(M + 1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int sharkNum;
			cin >> sharkNum;
			if (sharkNum)
				shark.push_back({ sharkNum,i,j });
		}
	}
	for (int i = 1; i <= M; i++) {
		int d;
		cin >> d;
		startDirection[i] = d;
	}
	
	for (auto sh : shark) {
		int s = get<0>(sh);
		int x = get<1>(sh);
		int y = get<2>(sh);
		board[x][y].push_back({ s,startDirection[s] });
	}

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= 4; j++) {
			int dir;
			for (int k = 0; k < 4; k++) {
				cin >> dir;
				direction[i][j].push_back(dir);
			}
		}
	}
}

bool is_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

void leave_smell() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!board[i][j].size())
				continue;
			smell[i][j] = { board[i][j][0].first,K};
		}
	}
}

void move_shark() {
	vii tmpBoard[MAX][MAX];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!board[i][j].size())
				continue;
			int num = board[i][j][0].first;
			int d = board[i][j][0].second;
			int nextD = 0;
			for (int k = 0; k < direction[num][d].size(); k++) {
				int nx = i + dx[direction[num][d][k]];
				int ny = j + dy[direction[num][d][k]];
				if (!is_range(nx, ny))
					continue;
				if (smell[nx][ny].second == 0&&board[nx][ny].size()==0) {
					nextD = direction[num][d][k];
					break;
				}
			}
			if (!nextD) {
				for (int k = 0; k < direction[num][d].size(); k++) {
					int nx = i + dx[direction[num][d][k]];
					int ny = j + dy[direction[num][d][k]];
					if (!is_range(nx, ny))
						continue;
					if (smell[nx][ny].first == num&&board[nx][ny].size()==0) {
						nextD = direction[num][d][k];
						break;
					}
				}
			}
			board[i][j].clear();
			tmpBoard[i + dx[nextD]][j + dy[nextD]].push_back({ num,nextD });
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < tmpBoard[i][j].size(); k++) {
				board[i][j].push_back(tmpBoard[i][j][k]);
			}
		}
	}
}

void minus_smell() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (smell[i][j].second == 0)
				continue;
			if (smell[i][j].second - 1 == 0)
				smell[i][j] = { 0,0 };
			else
				smell[i][j] = { smell[i][j].first,smell[i][j].second - 1 };
		}
	}
}

void eat_shark() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j].size() <= 1)
				continue;
			sort(board[i][j].begin(), board[i][j].end());
			pii p = board[i][j][0];
			board[i][j].clear();
			board[i][j].push_back(p);
		}
	}
}

bool is_answer() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!board[i][j].size())
				continue;
			cnt++;
		}
	}
	if (cnt == 1)
		return true;
	return false;
}

void print() {
	cout << '\n';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j].size();
		}
		cout << "\n";
	}
}

void solve() {
	int answer = 0;
	while (true) {
		leave_smell();
		move_shark();
		minus_smell();
		eat_shark();
		answer++;
		if (is_answer() || answer == 1000)
			break;
	}
	if (answer == 1000)
		cout << -1 << '\n';
	else
		cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
