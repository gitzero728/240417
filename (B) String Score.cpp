#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int NN = 101010;
int L[NN], R[NN], x[NN];
bool f[NN];

int findMaxScore(int N, int Q, vector<vector<int> > a) {
	int n = N, q = Q;
	for(int i = 0; i < q; i++) {
		L[i] = a[i][0], R[i] = a[i][1], x[i] = a[i][2];
	}
	
	int ans = 0;
	for(int s = 1 << n; s--; ) {
		for(int i = 1; i <= n; i++) {
			if((1 << i - 1) & s) f[i] = 1;
			else f[i] = 0;
		}
		int sum = 0;
		for(int i = 0; i < q; i++) {
			bool flag = 0;
			for(int j = L[i]; j <= R[i]; j++) {
				if(f[j]) flag = 1;
			}
			if(flag) sum += x[i];
		}
		ans = max(ans, sum);
	}
	return ans;
}

int main() {
#ifndef ONLINE_JUDGE
//	freopen("in.in", "r", stdin);
	//freopen("out.out", "w", stdout);
#endif
	
	int n, q; scanf("%d %d", &n, &q);
	vector<vector<int> > aa;
	for(int i = q; i--; ) {
		vector<int> vec;
		for(int j = 3; j--; ) {
			int x; scanf("%d", &x);
			vec.push_back(x);
		}
		aa.push_back(vec);
	}
	cout<<findMaxScore(n, q, aa);
	return 0;
}
