#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <tuple>

using namespace std;

int N;
vector<tuple<int,int>> v;
stack<int> st;

void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int center, radius;
	for (int i = 0; i < N; i++) {
		cin >> center >> radius;
		v.push_back({ center - radius,i });
		v.push_back({ center + radius,i });
	}
	sort(v.begin(), v.end());
}

bool solve() {
	for (int i = 0; i < v.size()-1; i++) {
		if (get<0>(v[i]) == get<0>(v[i + 1]))
			return false;
	}
	for (int i = 0; i < v.size(); i++) {
		if (st.empty())
			st.push(get<1>(v[i]));
		else if (get<1>(v[i]) == st.top())
			st.pop();
		else
			st.push(get<1>(v[i]));
	}
	if (st.empty())
		return true;
	else
		return false;
}

int main() {
	init();
	cout << (solve() ? "YES" : "NO") << '\n';
	return 0;
}