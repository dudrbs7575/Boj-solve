#include<iostream>
#include<algorithm>
#include <cmath>
using namespace std;
using ll = long long;

const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

int n;
ll p[555'555], maxLeft[555'555], maxRight[555'555];
int main() {
	cin >> n;
	ll sum = 0;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		sum += p[i];
	}
	
	ll m = p[0];
	maxLeft[0] = p[0];
	for (int i = 1; i < n; i++) {
		m = max(p[i], m + p[i]);
		maxLeft[i] = max(maxLeft[i - 1], m);
	}

	m = p[n - 1];
	maxRight[n-1] = p[n-1];
	for (int i = n-2; i >= 0; i--) {
		m = max(p[i], m + p[i]);
		maxRight[i] = max(maxRight[i + 1], m);
	}

	ll ans = -LLINF;
	for (int i = 0; i < n; i++) {
		ans = max(ans, sum + maxLeft[i] + maxRight[i+1]);
	}
	cout << ans;
}