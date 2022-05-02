#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector < pair<int, int>>;
using vvi = vector<vector<int>>;
using tiii = tuple<int, int, int>;

#define INF 0x3f3f3f3f
#define MAX 10

int N, W, T, K;
vi fire_power;
int tmp[MAX];
int start;
int answer = 0;


void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> W >> T >> K;
	fire_power.resize(MAX, 0);
	for (int i = 1; i <= N; i++)
		cin >> fire_power[i];
	start = W+1;
}

void fire_delete(vi &fire_power,int idx, bool flag) {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 1; i <= N ; i++) {
		if ((flag == false && i == idx) || !fire_power[i]) {
			tmp[i] = fire_power[i];
			continue;
		}
		int cnt = 0;
		if (fire_power[i - 1])
			cnt++;
		if (fire_power[i + 1])
			cnt++;
		tmp[i] = max(0, fire_power[i] - (3 - cnt));
	}
	for (int i = 1; i <= N; i++)
		fire_power[i] = tmp[i];
}

bool is_ans(int K, vi &fire_power) {
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		if (fire_power[i] > 0) 
			cnt++;
	}
	if (cnt >= K)
		return true;
	else
		return false;
}

void dfs(int idx, int time, int K,vi fire,bool flag) {
	if (idx == 0 || idx == N + 1)
		return;

	fire_delete(fire,idx,flag);

	if (time == T) {
		if (is_ans(K, fire))
			answer++;
		return;
	}
	for (int i = idx - 1; i <= idx + 1; i++) 
		dfs(i, time + 1, K, fire,false);
}

void solve() {
	dfs(start, 1, K,fire_power,true); //SKH 시작점, 놀이 시간, 유지해야하는 갯수
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}