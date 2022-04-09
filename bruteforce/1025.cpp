#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>

using namespace std;

#define MAX 10

int N, M;
char board[MAX][MAX];
int answer = -1;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	string s;
	for (int i = 0; i < N; i++) {
		cin >> s;
		for (int j = 0; j < M; j++)
			board[i][j] = s[j];
	}
}

bool isSquare(int x) {
	int tmp = sqrt(x);
	if (tmp * tmp == x)
		return true;
	return false;
}

void dfs(int i, int j, int x, int y, string s) {
	if (i < 0 || j < 0 || i >= N || j >= M)
		return;
	s += board[i][j];
	if (isSquare(stoi(s)))
		answer = max(answer, stoi(s));
	dfs(i + x, j + y, x, y, s);
}

void solve() {
	if (N == 1 && M == 1) {
		if (isSquare(board[0][0] - '0'))
			answer = board[0][0] - '0';
		return;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			for (int offX = -N + 1; offX < N; offX++) {
				string s = "";
				for (int offY = -M + 1; offY < M; offY++) {
					if (offX == 0 && offY == 0)
						continue;
					dfs(i, j, offX, offY, s);
				}
			}
		}
	}

}

int main() {
	init();
	solve();
	cout << answer << '\n';
	return 0;
}