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

#define ll long long
#define vvii vector<vector<pair<int,int>>>
#define vvi vector<vector<int>>
#define vii vector<pair<int,int>>
#define vi vector<int>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
#define MAX 10001

int N,M;
int arr[9];
vector<int> v;
int chk[9];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> arr[i];
}

void dfs(int cnt,int idx) {
	if (cnt == M) {
		for (auto a : v)
			cout << a << " ";
		cout << '\n';
		return;
	}

	for (int i = idx; i < N; i++) {
		if (chk[i] >= M)
			continue;
		chk[i]++;
		v.push_back(arr[i]);
		dfs(cnt + 1,i);
		chk[i]--;
		v.pop_back();
	}
}

void solve() {
	sort(arr, arr + N);
	dfs(0,0);
}

int main() {
	init();
	solve();
	return 0;
}
