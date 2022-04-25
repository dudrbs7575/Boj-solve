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
#define MAX 555
int N;
int board[MAX][MAX];
vector<tiii> coordi;
int dx[] = {0,1,0,-1};
int dy[] = {-1,0,1,0};
int answer = 0;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
}

void get_coordi() {
	int x = N / 2;
	int y = N / 2;
	
	int len = 1;
	int d = 0;
	int cnt = 0;
	while (true) {
		if (cnt == 2) {
			len++;
			cnt = 0;
		}
		if (d == 4)
			d = 0;
		for (int i = 0; i < len; i++) {
			x += dx[d];
			y += dy[d];
			coordi.push_back({ x,y,d });
			if (x == 0 && y == 0)
				break;
		}
		if (x == 0 && y == 0)
			break;
		cnt++;
		d++;
	}
}
//ÁÂ ÇÏ ¿ì »ó
//d=0 1 3
//d=1 0 2
//d=2 1 3
//d=3 0 2
//Ã³À½ 1Ä­¾¿ -1 1
//µÎ¹øÂ° 2Ä­¾¿ -1 1
//¼¼¹øÂ° 1Ä­¾¿ -1 1
//4¹øÂ° 0Ä­¾¿ -1 1

bool is_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

void spread_sand(int x, int y, int d) {
	if (!board[x][y])
		return;
	int onePercent = board[x][y] * 0.01;
	int twoPercent = board[x][y] * 0.02;
	int fivePercent = board[x][y] * 0.05;
	int sevenPercent = board[x][y] * 0.07;
	int tenPercent = board[x][y] * 0.1;
	int aPercent = board[x][y] - (2 * onePercent + 2 * twoPercent + 2 * sevenPercent + 2 * tenPercent + fivePercent);
	board[x][y] = 0;
	int n1 = d - 1;
	if (n1 == -1)
		n1 = 3;
	int n2 = d + 1;
	if (n2 == 4)
		n2 = 0;
	
	if (!is_range(x - dx[d] + dx[n1], y - dy[d] + dy[n1]))
		answer += onePercent;
	else 
		board[x - dx[d] + dx[n1]][y - dy[d] + dy[n1]] += onePercent;
	if (!is_range(x - dx[d] + dx[n2], y - dy[d] + dy[n2]))
		answer += onePercent;
	else
		board[x - dx[d] + dx[n2]][y - dy[d] + dy[n2]] += onePercent;


	int i;
	for (i = 1; i <= 3; i++) {
		if (i == 1) {
			if (!is_range(x + dx[n1], y + dy[n1])) 
				answer += sevenPercent;
			else 
				board[x + dx[n1]][y + dy[n1]] += sevenPercent;
			if (!is_range(x + dx[n2], y + dy[n2])) 
				answer += sevenPercent;
			else 
				board[x + dx[n2]][y + dy[n2]] += sevenPercent;

			if (!is_range(x + dx[n1] + dx[n1], y + dy[n1] + dy[n1])) 
				answer += twoPercent;
			else 
				board[x + dx[n1] + dx[n1]][y + dy[n1] + dy[n1]] += twoPercent;
			if (!is_range(x + dx[n2] + dx[n2], y + dy[n2] + dy[n2])) 
				answer += twoPercent;
			else 
				board[x + dx[n2] + dx[n2]][y + dy[n2] + dy[n2]] += twoPercent;
		}
		else if (i == 2) {
			if (!is_range(x + dx[n1], y + dy[n1])) 
				answer += tenPercent;
			else 
				board[x + dx[n1]][y + dy[n1]] += tenPercent;
			if (!is_range(x + dx[n2], y + dy[n2])) 
				answer += tenPercent;
			else 
				board[x + dx[n2]][y + dy[n2]] += tenPercent;
		}
		else {
			if (!is_range(x, y))
				answer += fivePercent;
			else
				board[x][y] += fivePercent;
		}
		x += dx[d];
		y += dy[d];
	}

	if (!is_range(x - dx[d]-dx[d], y - dy[d]-dy[d]))
		answer += aPercent;
	else
		board[x - dx[d]-dx[d]][y - dy[d]-dy[d]] += aPercent;
}

void move_tornado() {
	for (auto c : coordi) {
		int x = get<0>(c);
		int y = get<1>(c);
		int d = get<2>(c);
		spread_sand(x, y, d);
	}
}

void solve() {
	get_coordi();
	move_tornado();
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
