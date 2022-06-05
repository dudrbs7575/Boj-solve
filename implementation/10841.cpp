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

int N;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
}

bool cmp(pii& p1, pii& p2) {
	if (p1.first == p2.first)
		return p1.second < p2.second;
	return p1.first < p2.first;
}

void solve() {
	vector<pii> tmp;
	vector<pair<int, string>> origin;
	int age; string name;
	for (int i = 0; i < N; i++) {
		cin >> age >> name;
		origin.push_back({ age,name });
		tmp.push_back({ age,i });
	}
	sort(tmp.begin(), tmp.end(), cmp);
	
	for (auto p : tmp) {
		cout << p.first << " " << origin[p.second].second << '\n';
	}
}

int main() {
	init();
	solve();
	return 0;
}