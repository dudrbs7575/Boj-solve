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
vector<pair<string,int>> aligned_vector;
set<string> se;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	string s;
	while (N--) {
		cin >> s;
		if (se.find(s) == se.end()) {
			aligned_vector.push_back({ s,s.length() });
			se.insert(s);
		}
	}
}

bool cmp(pair<string,int> &p1, pair<string,int> &p2) {
	if (p1.second == p2.second)
		return p1.first < p2.first;
	return p1.second < p2.second;
}

void solve() {
	sort(aligned_vector.begin(), aligned_vector.end(), cmp);
	for (auto a : aligned_vector)
		cout << a.first << '\n';
}

int main() {
	init();
	solve();
	return 0;
}