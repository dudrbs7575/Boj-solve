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
#define MAX 12

int N, M, K;
vi board[MAX][MAX];
int feed[MAX][MAX];
int S2D2[MAX][MAX];
int dx[] = { -1,-1,-1,0,0,1,1,1 };
int dy[] = { -1,0,1,-1,1,-1,0,1 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); 
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> S2D2[i][j];
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			feed[i][j] = 5;
		}
	}

	int x, y, age;
	while (M--) {
		cin >> x >> y >> age;
		board[x][y].push_back(age);
	}
}

void spring_summer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			bool flag = false;
			vi tmp = board[i][j];
			sort(tmp.begin(), tmp.end());
			board[i][j].clear();
			for (int k = 0; k < tmp.size(); k++) {
				if (flag) {
					feed[i][j] += (tmp[k] / 2);
					continue;
				}
				if (feed[i][j] - tmp[k] < 0) {
					flag = true;
					feed[i][j] += (tmp[k] / 2);
					continue;
				}
				feed[i][j] -= tmp[k];
				board[i][j].push_back(tmp[k]+1);
			}
		}
	}
}

void fall() {
	vi tmp[MAX][MAX];
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 0; k < board[i][j].size(); k++) {
				if (board[i][j][k] % 5 == 0) {
					for (int z = 0; z < 8; z++) {
						int nx = i + dx[z];
						int ny = j + dy[z];
						tmp[nx][ny].push_back(1);
					}
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (tmp[i][j].size()) {
				for (int k = 0; k < tmp[i][j].size(); k++)
					board[i][j].push_back(tmp[i][j][k]);
			}
		}
	}
}

void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			feed[i][j] += S2D2[i][j];
		}
	}
}

void solve() {
	while (K--) {
		spring_summer();
		fall();
		winter();
	}
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			answer += board[i][j].size();
		}
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
