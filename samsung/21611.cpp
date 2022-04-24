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
#define MAX 51

int board[MAX][MAX];
int N, M;
int d, s;
int dx[] = { 0,-1,1,0,0 };
int dy[] = { 0,0,0,-1,1 };
int round_dx[] = { 0,1,0,-1 };
int round_dy[] = { -1,0,1,0 };
int beadCnt[4];
pii shark_loc;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); 
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> board[i][j];
		}
	}
}

void destroy_bead(int d, int s) {
	int nx = shark_loc.first;
	int ny = shark_loc.second;
	while (s--) {
		nx = nx+dx[d];
		ny = ny+dy[d];
		board[nx][ny] = 0;
	}
}

void rounding() {
	vi v;
	int length = 1;
	int cnt = 0;
	int d = 0;
	int nx = shark_loc.first;
	int ny = shark_loc.second;
	while (true) {
		if (d == 4)
			d = 0;
		if (cnt == 2) {
			cnt = 0;
			length++;
		}
		for (int i = 0; i < length; i++) {
			nx += round_dx[d];
			ny += round_dy[d];
			if (board[nx][ny] != 0) 
				v.push_back(board[nx][ny]);
			if (nx == 1 && ny == 1)
				break;
		}
		d++;
		cnt++;
		if (nx == 1 && ny == 1)
			break;
	}

	if (!v.size())
		return;
	
	memset(board, 0, sizeof(board));

	length = 1;
	cnt = 0;
	d = 0;
	nx = shark_loc.first;
	ny = shark_loc.second;
	int idx = 0;
	while (true) {
		if (d == 4)
			d = 0;
		if (cnt == 2) {
			cnt = 0;
			length++;
		}
		for (int i = 0; i < length; i++) {
			if (idx == v.size())
				break;
			nx += round_dx[d];
			ny += round_dy[d];
			board[nx][ny] = v[idx];
			idx++;
			if (nx==1&&ny==1)
				break;
		}
		d++;
		cnt++;
		if (idx == v.size()|| (nx == 1 && ny == 1))
			break;
	}
}

bool destroy_four_bead_rounding() {
	vi v;
	int length = 1;
	int cnt = 0;
	int d = 0;
	int nx = shark_loc.first;
	int ny = shark_loc.second;
	while (true) {
		if (d == 4)
			d = 0;
		if (cnt == 2) {
			cnt = 0;
			length++;
		}
		for (int i = 0; i < length; i++) {
			nx += round_dx[d];
			ny += round_dy[d];
			if (board[nx][ny] != 0)
				v.push_back(board[nx][ny]);
			if (nx == 1 && ny == 1)
				break;
		}
		d++;
		cnt++;
		if (nx == 1 && ny == 1)
			break;
	}
	
	if (!v.size())
		return true;

	vii range;
	int flag = 0;
	int pre = -1;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] != pre) {
			if (pre != -1&&flag>=4) {
				range.push_back({i-flag,i-1});
			}
			pre = v[i];
			flag = 1;
		}
		else {
			flag++;
		}
	}
	if (flag >= 4)
		range.push_back({ v.size() - flag,v.size() - 1 });
	
	if (!range.size())
		return true;

	for (auto r : range) {
		for (int i = r.first; i <= r.second; i++) {
			beadCnt[v[i]]++;
			v[i] = 0;
		}
	}

	vi vv;
	for (auto a : v) {
		if (a != 0)
			vv.push_back(a);
	}

	if (!vv.size())
		return true;

	memset(board, 0, sizeof(board));

	length = 1;
	cnt = 0;
	d = 0;
	nx = shark_loc.first;
	ny = shark_loc.second;
	int idx = 0;
	while (true) {
		if (d == 4)
			d = 0;
		if (cnt == 2) {
			cnt = 0;
			length++;
		}
		for (int i = 0; i < length; i++) {
			if (idx == vv.size())
				break;
			nx += round_dx[d];
			ny += round_dy[d];
			board[nx][ny] = vv[idx];
			idx++;
			if ((nx == 1 && ny == 1))
				break;
		}
		d++;
		cnt++;
		if (idx == vv.size()|| (nx == 1 && ny == 1))
			break;
	}

	return false;
}

void change_bead() {
	vi v;
	int length = 1;
	int cnt = 0;
	int d = 0;
	int nx = shark_loc.first;
	int ny = shark_loc.second;
	while (true) {
		if (d == 4)
			d = 0;
		if (cnt == 2) {
			cnt = 0;
			length++;
		}
		for (int i = 0; i < length; i++) {
			nx += round_dx[d];
			ny += round_dy[d];
			if (board[nx][ny] != 0) 
				v.push_back(board[nx][ny]);
			if (nx == 1 && ny == 1)
				break;
		}
		d++;
		cnt++;
		if (nx == 1 && ny == 1)
			break;
	}

	if (!v.size())
		return;

	vi vv;
	int flag = 0;
	int pre = -1;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] != pre) {
			if (pre != -1) {
				vv.push_back(flag);
				vv.push_back(pre);
			}
			pre = v[i];
			flag = 1;
		}
		else {
			flag++;
		}
	}
	vv.push_back(flag);
	vv.push_back(pre);

	memset(board, 0, sizeof(board));

	length = 1;
	cnt = 0;
	d = 0;
	nx = shark_loc.first;
	ny = shark_loc.second;
	int idx = 0;
	while (true) {
		if (d == 4)
			d = 0;
		if (cnt == 2) {
			cnt = 0;
			length++;
		}
		for (int i = 0; i < length; i++) {
			if (idx == vv.size())
				break;
			nx += round_dx[d];
			ny += round_dy[d];
			board[nx][ny] = vv[idx];
			idx++;
			if (nx==1&&ny==1)
				break;
		}
		d++;
		cnt++;
		if (idx == vv.size() || (nx == 1 && ny == 1))
			break;
	}
}

void solve() {
	shark_loc = { (N + 1) / 2,(N + 1) / 2 };
	while (M--) {
		cin >> d >> s;
		destroy_bead(d,s);
		rounding();
		while (true) {
			if (destroy_four_bead_rounding()) 
				break;
		}
		change_bead();
	}
	cout << beadCnt[1] + beadCnt[2] * 2 + beadCnt[3] * 3 << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
