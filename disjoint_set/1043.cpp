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
#include <queue>

using namespace std;

#define vvii vector<vector<pair<int,int>>>
#define vvi vector<vector<int>>
#define vii vector<pair<int,int>>
#define vi vector<int>
#define pii pair<int,int>
#define INF 0x3f3f3f3f
#define MAX 51

//진실을 아는 사람이 있을 경우 진실을 말함.
//단 그 때 진실을 들었던 사람이 있는 다른 파티에서는 거짓말 못함.
int N, M, knowing;
vi knowTruth;
int parent[MAX];
vvi partyInfo;


void init() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> knowing;
	partyInfo.resize(M + 1);
	int person;
	while(knowing--) {
		cin >> person;
		knowTruth.push_back(person);
	}
	int people;
	for (int i = 1; i <= M; i++) {
		cin >> people;
		while (people--) {
			cin >> person;
			partyInfo[i].push_back(person);
		}
	}
}

int find_parent(int A) {
	if (A == parent[A])
		return A;
	return parent[A] = find_parent(parent[A]);
}

void Union(int A, int B) {
	A = find_parent(A);
	B = find_parent(B);
	parent[B] = A;
}

void solve() {
	int lie = M;
	for (int i = 1; i <= N; i++)
		parent[i] = i;

	for (int i = 1; i <= M; i++) {
		int N1 = partyInfo[i][0];
		for (int j = 1; j < partyInfo[i].size(); j++) {
			int N2 = partyInfo[i][j];
			Union(N1, N2);
		}
	}

	for (int i = 1; i <= M; i++) {
		bool flag = false;
		for (int j = 0; j < partyInfo[i].size(); j++) {
			if (flag)
				break;
			int N1 = partyInfo[i][j];
			for (int k = 0; k < knowTruth.size(); k++) {
				int N2 = knowTruth[k];
				if (find_parent(N1) == find_parent(N2)) {
					flag = true;
					break;
				}
			}
		}
		if (flag)
			lie--;
	}
	cout << lie << '\n';
}

int main() {
	init();
	solve();
	return 0;
}
