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

//recommend G x �˰��� �з� G�ΰ� �� ���� ����� ���� ��ȣ ���, �������� ���� ��ȣ ���� ū ��, -1�̸� �ݴ�
//recommend2 x �˰��� �з� ������� ���� ����� ����, �������� ���� ��ȣ ���� ū ��, -1�̸� �ݴ�
//recommend3 x L �˰��� �з� ������� ���̵� L���� ũ�ų� ���� ���� �� ���� ���� ��ȣ. �������� ��ȣ ���� ������, -1 �̸� �ݴ�
//add P L G ���̵� L�̰� �˰��� �з��� G�� ���� ��ȣP �߰�.
//solved P ����Ʈ���� ��ȣ P����

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