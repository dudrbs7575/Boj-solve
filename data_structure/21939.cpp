#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <set>

using namespace std;
using ll = long long;
using vi = vector<int>;

multiset<pair<int, int>> hard;	//난이도, 문제번호
map<int, int> ma;	//문제 번호, 난이도

int N, M;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int P, L;
	for (int i = 0; i < N; i++) {
		cin >> P >> L;
		hard.insert({ L,P });
		ma[P] = L;
	}
}

void solve() {
	cin >> M;
	while (M--) {
		string ope;
		int v1, v2;
		cin >> ope;
		if (ope == "recommend") {
			cin >> v1;
			if (v1 == 1) {
				auto it = --hard.end();
				cout << it->second << '\n';
			}
			else {
				auto it = hard.begin();
				cout << it->second << '\n';
			}
		}
		else if (ope == "add") {
			cin >> v1 >> v2;
			ma[v1] = v2;
			hard.insert(make_pair(v2, v1));
		}
		else {
			cin >> v1;
			int level = ma[v1];
			auto it = hard.find({ level,v1 });
			hard.erase(it);
			ma.erase(v1);
		}
	}
}

int main() {
	init();
	solve();
	return 0;
}