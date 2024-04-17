#include<bits/stdc++.h>
#define y second
#define x first

using namespace std;
using INT = long long;
using pii = pair<int, int>;

const int NN = 1010, mod = 1e9 + 7, all = (1 << 10) - 1;

vector<int> adj[NN];
int val[NN];
int dp[NN][all + 1];

int state(int x) {
	vector<int> a;
	while(x) a.push_back(x % 10), x /= 10;
	sort(a.begin(), a.end());
	
	int s = 1 << a[0];
	for(int i = 1; i < a.size(); i++) {
		if(a[i - 1] == a[i]) return -1;
		s |= 1 << a[i];
	}
	return s;
}

int dfs(int u) {
	int ans = 0, s = state(val[u]);
	if(~s) dp[u][s] = val[u];
	for(int v : adj[u]) {
		ans = (ans + dfs(v)) % mod;
		for(int s = all; s >= 0; s--) {
			for(int a = s; ; a = (a - 1) & s) {
				dp[u][s] = max(dp[u][s], dp[u][a] + dp[v][s ^ a]);
				if(a == 0) break;
			}
		}
	}
	ans = (ans + *max_element(dp[u], dp[u] + all + 1)) % mod;
	return ans;
}

int get_ans(int n, vector<int> par, vector<int> a) {
	for(int i = 2; i <= n; i++) {
		adj[par[i - 1]].push_back(i);
	}
	for(int i = 1; i <= n; i++) val[i] = a[i - 1];
	return dfs(1);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	//freopen("out.out", "w", stdout);
#endif
	
	int n; scanf("%d", &n);
	vector<int> par, a;
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		par.push_back(x);
	}
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		a.push_back(x);
	}
	cout<<get_ans(n, par, a);
	return 0;
}