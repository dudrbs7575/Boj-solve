#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>

using namespace std;

int N;
priority_queue<int, vector<int>, greater<int>> pq;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	int val;
	for (int i = 0; i < N * N; i++) {
		cin >> val;
		pq.push(val);
		if (pq.size() == N+1)
			pq.pop();
	}
	cout << pq.top();
	return 0;
}