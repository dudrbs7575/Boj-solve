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
using ll = long long;

#define INF 0x3f3f3f3f

int N;
vector<int> v;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	v.resize(N);
	for (int i = 0; i < N; i++)
		cin >> v[i];
}

int get_ans() {
	int sum = 0;
	for (int i = 0; i < N - 1; i++) 
		sum += abs(v[i] - v[i + 1]);
	return sum;
}

void solve() {
	int answer = -1;
	sort(v.begin(), v.end());
	do {
		answer = max(answer, get_ans());
	} while (next_permutation(v.begin(), v.end()));
	cout << answer << '\n';
}

int main() {
	init();
	solve();
	return 0;
}