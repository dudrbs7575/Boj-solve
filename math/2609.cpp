#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <tuple>
#include <sstream>

using namespace std;

#define vvii vector<vector<pair<int,int>>>
#define vvi vector<vector<int>>
#define vii vector<pair<int,int>>
#define vi vector<int>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
#define MAX 10000010

int A, B;

int gcd(int a, int b) {
	int n;
	while (b != 0) {
		n = a % b;
		a = b;
		b = n;
	}
	return a;
}

int lcm(int a, int b, int gcd) {
	return (a * b) / gcd;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> A >> B;
	int gcdAns = gcd(A, B);
	int lcmAns = lcm(A, B, gcdAns);
	cout << gcdAns << '\n';
	cout << lcmAns << '\n';
	return 0;
}
