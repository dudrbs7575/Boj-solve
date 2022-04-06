#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <functional>
#include <string>
#include <stack>
#include <queue>

using namespace std;

#define MAX 21
#define INF 0x3f3f3f3f

int N;
int graph[MAX][MAX];
bool chk[MAX][MAX];
int answer;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> graph[i][j];
		}
	}
	memset(chk, true, sizeof(chk));
}

bool floyd() {
	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (i == j || j == k || i == k)
					continue;
				if (graph[i][j] > graph[i][k] + graph[k][j]) 
					return false;
				if (graph[i][j] == graph[i][k] + graph[k][j])
					chk[i][j] = false;
			}
		}
	}
	return true;
}

void solve() {
	if (!floyd()) {
		cout << -1 << '\n';
		return;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = i+1; j <= N; j++) {
			if (!chk[i][j])
				continue;
			answer += graph[i][j];
		}
	}
	cout << answer << '\n';
}

int main(){
	init();
	solve();
	return 0;
}