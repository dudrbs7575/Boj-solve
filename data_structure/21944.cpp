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

//recommend G x 알고리즘 분류 G인것 중 가장 어려운 문제 번호 출력, 여러개면 문제 번호 가장 큰 것, -1이면 반대
//recommend2 x 알고리즘 분류 상관없이 가장 어려운 문제, 여러개면 문제 번호 가장 큰 것, -1이면 반대
//recommend3 x L 알고리즘 분류 상관없이 난이도 L보다 크거나 같은 문제 중 가장 쉬운 번호. 여러개면 번호 가장 작은것, -1 이면 반대
//add P L G 난이도 L이고 알고리즘 분류가 G인 문제 번호P 추가.
//solved P 리스트에서 번호 P제거

map<int, multiset<pair<int, int>>> group;
multiset<pair<int, int>> level;
multiset<pair<int, int>>::reverse_iterator rit;
map<int, pair<int, int>> find_value;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;
	int p, l, g;
	for (int i = 0; i < N; i++) {
		cin >> p >> l >> g;
		group[g].insert({ l,p });
		level.insert({ l,p });
		find_value[p] = { l,g };
	}
}

void execute_ope(string s) {
	if (s == "recommend") {
		int g, x;
		cin >> g >> x;
		if (x == 1) {
			cout<< (--group[g].end())->second << '\n';
		}
		else {
			cout << group[g].begin()->second << '\n';
		}
	}
	else if (s == "recommend2") {
		int x;
		cin >> x;
		if (x == 1) {
			cout << (--level.end())->second << '\n';
		}
		else {
			cout << (level.begin())->second << '\n';
		}

	}
	else if (s == "recommend3") {
		int x, l;
		cin >> x >> l;
		if (x == 1) {
			auto iter = level.lower_bound({ l,-1 });
			(iter == level.end()) ? cout << -1 << '\n' : cout << iter->second << '\n';
		}
		else {
			auto iter = level.upper_bound({ l,-1 });
			(iter == level.begin() || iter == level.end()) ? cout << -1 << '\n' : cout << (--iter)->second << '\n';
		}
	}
	else if (s == "add") {
		int p, l, g;
		cin >> p >> l >> g;
		group[g].insert({ l,p });
		level.insert({ l,p });
		find_value[p] = { l,g };
	}
	else {
		int p;
		cin >> p;
		int l = find_value[p].first;
		int g = find_value[p].second;
		group[g].erase({ l,p });
		level.erase({ l,p });
		find_value.erase(p);
	}
}

void solve() {
	int M;
	cin >> M;
	string ope;
	while (M--) {
		cin >> ope;
		execute_ope(ope);
	}
}

int main() {
	init();
	solve();
	return 0;
}