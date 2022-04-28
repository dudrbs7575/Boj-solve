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
#define MAX 222

int durability[MAX];
bool robot[MAX];

//로봇을 1번에 올리고 N번에서 내림
//벨트 로봇과 함께 회전
//먼저 벨트에 올라간 로봇부터 앞으로 한 칸 이동,내구도 감소
//올리는 위치 내구도 0 아니면 로봇 올리기, 내구도 1 감소
//내구도가 0인 칸의 갯수가 K개 이상이면 과정 종료

int N, K;
int len;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> K;
	len = 2 * N;
	for (int i = 1; i <= len; i++)
		cin >> durability[i];
}

bool is_zero_k() {
	int cnt = 0;
	for (int i = 1; i <= len; i++) {
		if (!durability[i])
			cnt++;
	}
	if (cnt >= K)
		return true;
	return false;
}

void rounding() {
	int tmp = durability[len];
	bool tmp2 = robot[len];
	for (int i = len; i >= 2; i--) {
		durability[i] = durability[i - 1];
		robot[i] = robot[i - 1];
	}
	if (robot[N])
		robot[N] = false;	//로봇 내리기
	durability[1] = tmp;
	robot[1] = tmp2;
}

void move_robot() {
	for (int i = N-1; i >= 1; i--) {
		if (!robot[i])
			continue;
		if (durability[i+1] && !robot[i+1]) {	//내구도가 1이상, robot이 존재X
			robot[i + 1] = true;
			durability[i+1] -= 1;
			robot[i] = false;
		}
	}
	if (robot[N])
		robot[N] = false;
}

void put_robot() {
	if (!robot[1] && durability[1]) {
		robot[1] = true;
		durability[1] -= 1;
	}
}

void print() {
	cout << '\n';
	for (int i = 1; i <= len; i++)
		cout << durability[i] << " ";
	cout << '\n';
	for (int i = 1; i <= len; i++)
		cout << robot[i] << " ";
}

void solve() {
	int cnt = 1;
	while (true) {
		rounding();
		move_robot();
		put_robot();
		if (is_zero_k())
			break;
		cnt++;
	}
	cout << cnt << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
