#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <queue>

using namespace std;

#define MAX 100001
#define INF 987654321

int visit[MAX];

int solve(int N, int K) {
	queue<int> q;
	q.push(N);
	visit[N] = 0;
	while (!q.empty()) {
		int loc = q.front();
		q.pop();
		if (loc == K)
			return visit[K];
		
		if (loc + 1 < MAX && visit[loc + 1] > visit[loc] + 1) {
			visit[loc + 1] = visit[loc] + 1;
			q.push(loc + 1);
		}
		if (0 <= loc - 1 && visit[loc - 1] > visit[loc] + 1) {
			visit[loc - 1] = visit[loc] + 1;
			q.push(loc - 1);
		}
		if (loc * 2 < MAX && visit[loc * 2] > visit[loc]) {
			visit[loc * 2] = visit[loc];
			q.push(loc * 2);
		}
	}
}

int main() {
	int N, K;
	cin >> N >> K;
	for (int i = 0; i < MAX; i++)
		visit[i] = INF;
	cout << solve(N,K);
	return 0;
}