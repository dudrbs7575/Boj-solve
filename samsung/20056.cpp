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
#define MAX 55

vector<tiii> board[MAX][MAX];
vector<tiii> tmpBoard[MAX][MAX];
int dx[] = { -1,-1,0,1,1,1,0,-1 };
int dy[] = { 0,1,1,1,0,-1,-1,-1 };
int N, M, K;

//벽의 끝은 벽의 처음과 연결
//di, si만큼 이동
//2개 이상 파이어볼 존재 칸 4개로 나뉘어짐
//질량은 모든질량/5
//속력은 모든속력/파이어볼갯수
//방향 방향이 모두 홀수이면, 0,2,4,6 , 그렇지 않을 시 1,3,5,7
//이 과정에서 질량이 0인 파이어볼은 소멸됨 


void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> K;
	int r, c, m, s, d;
	while (M--) {
		cin >> r >> c >> m >> s >> d;
		board[r][c].push_back({ m,s,d });	//질량, 속력, 방향
	}
}

void clear() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			tmpBoard[i][j].clear();
		}
	}
}

void move_fireball() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 0; k < board[i][j].size(); k++) {
				tiii t = board[i][j][k];
				int m = get<0>(t); int s = get<1>(t); int d = get<2>(t);
				int x = i; int y = j;
				int tmpS = s;
				while (tmpS--) {
					x += dx[d];
					y += dy[d];
					if (x == 0)
						x = N;
					if (y == 0)
						y = N;
					if (x == N + 1)
						x = 1;
					if (y == N + 1)
						y = 1;
				}
				tmpBoard[x][y].push_back(t);
			}
			board[i][j].clear();
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			board[i][j] = tmpBoard[i][j];
		}
	}
}

void split_fireball() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (board[i][j].size() <= 1)
				continue;
			int splitM = 0; int splitS = 0; int splitD = 0;
			int oddCnt = 0;
			int evenCnt = 0;
			for (int k = 0; k < board[i][j].size(); k++) {
				tiii t = board[i][j][k];
				splitM += get<0>(t);
				splitS += get<1>(t);
				if (get<2>(t) % 2 == 0)
					evenCnt++;
				else
					oddCnt++;
			}
			int afterM = splitM / 5; int afterS = splitS / board[i][j].size();
			int afterD = (oddCnt == board[i][j].size() || evenCnt == board[i][j].size()) ? 0 : 1;
			board[i][j].clear();
			if (!afterM)
				continue;
			board[i][j].push_back({ afterM,afterS,afterD });
			board[i][j].push_back({ afterM,afterS,afterD+2 });
			board[i][j].push_back({ afterM,afterS,afterD+4 });
			board[i][j].push_back({ afterM,afterS,afterD+6 });
		}
	}
}

int get_answer() {
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 0; k < board[i][j].size(); k++) {
				ans += get<0>(board[i][j][k]);
			}
		}
	}
	return ans;
}

void print() {
	cout << '\n';
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << board[i][j].size();
		}
		cout << '\n';
	}
}

void solve() {
	while (K--) {
		//print();
		clear();
		move_fireball();
		//print();
		split_fireball();
	}
	cout << get_answer() << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
