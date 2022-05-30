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

queue<int> qu;
int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	for (int i = 1; i <= N; i++)
		qu.push(i);
}

void solve() {
	if (N == 1) {
		cout << qu.front() << '\n';
		return;
	}
	int answer;
	while (true) {
		qu.pop();
		if (qu.size()==1) {
			cout << qu.front() << '\n';
			return;
		}
		qu.push(qu.front());
		qu.pop();
	}
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}