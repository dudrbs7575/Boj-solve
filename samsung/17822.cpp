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
#define MAX 55

//x , d , k
//번호가 x의 배수인 원판을 d(d==0 시계, d==1 반시계)방향으로 k칸 회전
//인접하면서 같은 수를 모두 지움
//없는 경우에는 원판에 적힌 수의 평균을 구하고 평균 보다 큰 수에는 1을 빼고
//작은 수에는 1을 더한다.

int N, M, T;
vvi board;
bool chk[MAX][MAX];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> T;
	board.resize(N + 1);
	int p;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> p;
			board[i].push_back(p);
		}
	}
}

bool is_range(int x, int y) {
	return 1 <= x && x <= N && 0 <= y && y < M;
}

void rounding_board(int n, int dir, int k) {
	int multiple = 1;
	//dir=0 시계, dir=1 반시계
	while (true) {
		int row = multiple * n;
		if (row > N)
			break;
		vi tmp;
		if (dir == 0) {
			int idx = M - k;
			for (int i = idx; i < M; i++)
				tmp.push_back(board[row][i]);
			for (int i = 0; i < idx; i++)
				tmp.push_back(board[row][i]);
		}
		else {
			int idx = k;
			for (int i = idx; i < M; i++)
				tmp.push_back(board[row][i]);
			for (int i = 0; i < idx; i++)
				tmp.push_back(board[row][i]);
		}
		board[row] = tmp;
		multiple++;
	}
}

bool find_same_point() {
	memset(chk, false, sizeof(chk));
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M-1; j++) {
			if (!board[i][j] || !board[i][j + 1])
				continue;
			if (board[i][j] == board[i][j + 1]) {
				chk[i][j] = true;
				chk[i][j + 1] = true;
				cnt++;
			}
		}
		if (!board[i][0] || !board[i][M - 1])
			continue;
		if (board[i][0] == board[i][M - 1]) {
			chk[i][0] = true;
			chk[i][M - 1] = true;
			cnt++;
		}
	}
	for (int j = 0; j < M; j++) {
		for (int i = 1; i < N; i++) {
			if (!board[i][j] || !board[i + 1][j])
				continue;
			if (board[i][j] == board[i + 1][j]) {
				chk[i][j] = true;
				chk[i + 1][j] = true;
				cnt++;
			}
		}
	}
	if (!cnt)
		return false;

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (chk[i][j])
				board[i][j] = 0;
		}
	}
	return true;
}

void resize_board() {
	double mean = 0;
	double cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j]) {
				mean += (double)board[i][j];
				cnt++;
			}
		}
	}
	mean /= cnt;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if ((double)board[i][j] == mean||!board[i][j])
				continue;
			((double)board[i][j] > mean) ? board[i][j] -= 1 : board[i][j] += 1;
		}
	}
}

int get_ans() {
	int answer = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			answer += board[i][j];
		}
	}
	return answer;
}

void print() {
	cout << '\n';
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			cout << board[i][j] << " ";
		}
		cout << '\n';
	}
}

void solve() {
	int x, d, k;
	while (T--) {
		cin >> x >> d >> k;
		rounding_board(x, d, k);
		if (!find_same_point()) {
			resize_board();
		}
	}
	cout << get_ans() << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
