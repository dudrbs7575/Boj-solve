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
#define MAX 444

int board[MAX][MAX];
vvi like;
vi order;
int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };
int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	like.resize(N*N + 1);
	int k, p1, p2, p3, p4;
	for (int i = 0; i < N * N; i++) {
		cin >> k >> p1 >> p2 >> p3 >> p4;
		order.push_back(k);
		like[k].push_back(p1);
		like[k].push_back(p2);
		like[k].push_back(p3);
		like[k].push_back(p4);
	}
}

bool is_range(int x, int y) {
	return 1 <= x && x <= N && 1 <= y && y <= N;
}

void get_seat(int person) {
	int allEmpty = -1;
	int allF = -1;
	int seatX = 0;
	int seatY = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (board[i][j])
				continue;
			int empty = 0;
			int f = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (!is_range(nx, ny))
					continue;
				if (board[nx][ny] == 0)
					empty++;
				else {
					for (int z = 0; z < like[person].size(); z++) {
						if (like[person][z] == board[nx][ny])
							f++;
					}
				}
			}
			if (allF < f) {
				seatX = i;
				seatY = j;
				allF = f;
				allEmpty = empty;
			}
			else if (allF == f) {
				if (allEmpty < empty) {
					seatX = i;
					seatY = j;
					allEmpty = empty;
				}
			}
		}
	}
	board[seatX][seatY] = person;
}

int get_point() {
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int person = board[i][j];
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (!is_range(nx, ny))
					continue;
				for (int z = 0; z < like[person].size(); z++) {
					if (like[person][z] == board[nx][ny])
						cnt++;
				}
			}
			if (cnt == 0)
				ans += 0;
			else if (cnt == 1)
				ans += 1;
			else if (cnt == 2)
				ans += 10;
			else if (cnt == 3)
				ans += 100;
			else
				ans += 1000;
		}
	}
	return ans;
}

void solve() {
	memset(board, 0, sizeof(board));
	for (auto o : order) 
		get_seat(o);
	
	int answer = get_point();
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
