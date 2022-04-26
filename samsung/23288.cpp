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
#define MAX 22

int board[MAX][MAX];
bool visited[MAX][MAX];
int N, M, K;
int dice[6] = {2,4,5,3,1,6}; // ¾Õ, ÁÂ, µÚ, ¿ì, À§, ¹Ø
pii diceLoc = { 0,0 };
int d = 0;
int dx[] = { 0,1,0,-1 };	//µ¿ ³² ¼­ ºÏ
int dy[] = { 1,0,-1,0 };

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
}

bool is_range(int x, int y) {
	return 0 <= x && x < N && 0 <= y && y < M;
}

int get_direction(int d) {
	if (is_range(diceLoc.first + dx[d], diceLoc.second + dy[d]))
		return d;
	d = (d + 2) % 4;
	return d;
}

void move_dice() {
	d = get_direction(d);
	int x = diceLoc.first;
	int y = diceLoc.second;
	int tmpDice[6] = { dice[0],dice[1],dice[2],dice[3],dice[4],dice[5] };
	if(d == 0){ //µ¿
		dice[0] = tmpDice[0]; dice[1] = tmpDice[5]; dice[2] = tmpDice[2]; dice[3] = tmpDice[4]; dice[4] = tmpDice[1]; dice[5] = tmpDice[3];
		diceLoc = { x + dx[d],y + dy[d] };
	}
	else if (d == 1) {  //³²
		dice[0] = tmpDice[5]; dice[1] = tmpDice[1]; dice[2] = tmpDice[4]; dice[3] = tmpDice[3]; dice[4] = tmpDice[0]; dice[5] = tmpDice[2];
		diceLoc = { x + dx[d],y + dy[d] };
	}
	else if (d == 2) {  //¼­
		dice[0] = tmpDice[0]; dice[1] = tmpDice[4]; dice[2] = tmpDice[2]; dice[3] = tmpDice[5]; dice[4] = tmpDice[3]; dice[5] = tmpDice[1];
		diceLoc = { x + dx[d],y + dy[d] };
	}
	else {  //ºÏ
		dice[0] = tmpDice[4]; dice[1] = tmpDice[1]; dice[2] = tmpDice[5]; dice[3] = tmpDice[3]; dice[4] = tmpDice[2]; dice[5] = tmpDice[0];
		diceLoc = { x + dx[d],y + dy[d] };
	}
}

pii get_point() {
	memset(visited, false, sizeof(visited));
	queue<pii> qu;
	int cnt = 1;
	int point = board[diceLoc.first][diceLoc.second];
	qu.push({ diceLoc.first,diceLoc.second });
	visited[diceLoc.first][diceLoc.second] = true;
	while (!qu.empty()) {
		int x = qu.front().first;
		int y = qu.front().second;
		qu.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!is_range(nx, ny) || visited[nx][ny] || board[nx][ny] != point)
				continue;
			qu.push({ nx,ny });
			visited[nx][ny] = true;
			cnt++;
		}
	}
	return { cnt,point };
}

void change_direction() {
	int x = diceLoc.first;
	int y = diceLoc.second;
	if (dice[5] > board[x][y]) {
		d = (d + 1) % 4;
	}
	else if (dice[5] < board[x][y]) {
		d = (d - 1);
		if (d == -1)
			d = 3;
	}
}

void solve() {
	int answer = 0;
	while (K--) {
		move_dice();
		cout << diceLoc.first+1 << "," << diceLoc.second+1 << '\n';
		pii p=get_point();
		answer += (p.first * p.second);
		change_direction();
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
