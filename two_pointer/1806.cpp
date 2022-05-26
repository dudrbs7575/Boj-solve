#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <set>
#include <queue>
#include <stack>

using namespace std;
using pii = pair<int, int>;

#define INF 0x3f3f3f3f

int N, S;
int arr[100'001];

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> S;
	for (int i = 0; i < N; i++)
		cin >> arr[i];
}

void solve() {
	int partial_sum = 0;
	int head = 0;
	int tail = 0;
	int answer = INF;
	while (head <= tail) {
		if (partial_sum >= S) {
			answer = min(answer, tail - head);
			partial_sum -= arr[head++];
		}
		else if (tail == N)
			break;
		else 
			partial_sum += arr[tail++];
	}
	(answer == INF) ? cout << 0 << '\n' : cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}