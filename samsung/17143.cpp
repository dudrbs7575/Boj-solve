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
using piii = pair<pair<int, int>, int>;
using tiii = tuple<int, int, int>;
using tiiii = tuple<int, int, int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vii = vector<pair<int, int>>;


#define INF 0x3f3f3f3f
#define MAX 111

vector<tiii> board[MAX][MAX];	//크기, 속력, 이동 방향
int fisherMan = 0;
int R, C, M;
int dx[] = {0,-1,1,0,0};	//북, 남, 동, 서
int dy[] = {0,0,0,1,-1};

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> R >> C >> M;
	int x, y, s, d, z;
	while(M--) {
		cin >> x >> y >> s >> d >> z;
		board[x][y].push_back({ z,s,d });
	}
}

bool cmp(tiii &t, tiii &t2) {
	return get<0>(t) > get<0>(t2);
}

bool is_range(int x, int y) {
	return 1 <= x && x <= R && 1 <= y && y <= C;
}

int fishing_shark() {
	for (int i = 1; i <= R; i++) {
		if (!board[i][fisherMan].size())
			continue;
		tiii t = board[i][fisherMan][0];
		board[i][fisherMan].clear();
		return get<0>(t);
	}
	return 0;
}

void shark_move() {
	vector<tiii> tmpBoard[MAX][MAX];
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (!board[i][j].size())
				continue;
			tiii t = board[i][j][0];
			int x = i; int y = j;
			int s = get<1>(t); int d = get<2>(t);
			int tmpS = s;
			while (true) {
				if (tmpS <= 0)
					break;
				//북, 남, 동, 서
				if (d == 1) {
					if (x -tmpS > 1) {
						x -= tmpS;
						tmpS = 0;
					}
					else if (x - tmpS == 1) {
						x = 1;
						d = 2;
						tmpS = 0;
					}
					else {
						tmpS -= (x - 1);
						x = 1;
						d = 2;
					}
				}
				else if (d == 2) {
					if (x + tmpS < R) {
						x += tmpS;
						tmpS = 0;
					}
					else if (x + tmpS == R) {
						x = R;
						d = 1;
						tmpS = 0;
					}
					else {
						tmpS -= (R - x);
						x = R;
						d = 1;
					}
				}
				else if (d == 3) {
					if (y + tmpS < C) {
						y += tmpS;
						tmpS = 0;
					}
					else if (y + tmpS == C) {
						y = C;
						d = 4;
						tmpS = 0;
					}
					else {
						tmpS -= (C - y);
						y = C;
						d = 4;
					}
				}
				else {
					if (y - tmpS > 1) {
						y -= tmpS;
						tmpS = 0;
					}
					else if (y - tmpS == 1) {
						y = 1;
						d = 3;
						tmpS = 0;
					}
					else {
						tmpS -= (y - 1);
						y = 1;
						d = 3;
					}
				}
				/*
				x += dx[d];
				y += dy[d];
				if (!is_range(x, y)) {
					s++;
					if (d == 1)
						d = 2;
					else if (d == 2)
						d = 1;
					else if (d == 3)
						d = 4;
					else
						d = 3;
					x += dx[d];
					y += dy[d];
				}
				*/
			}
			get<1>(t) = s;
			get<2>(t) = d;
			tmpBoard[x][y].push_back(t);
		}
	}

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			board[i][j].clear();
			board[i][j] = tmpBoard[i][j];
		}
	}
}

void maximum_shark_eat() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (board[i][j].size()<=1)
				continue;
			sort(board[i][j].begin(), board[i][j].end(), cmp);
			tiii t = board[i][j][0];
			board[i][j].clear();
			board[i][j].push_back(t);
		}
	}
}

void solve() {
	int answer = 0;
	while (true) {
		fisherMan += 1;
		if (fisherMan == C + 1)
			break;
		answer += fishing_shark();
		shark_move();
		maximum_shark_eat();

	}
	cout << answer << '\n';
}


int main() {
	init();
	solve();
	return 0;
}
