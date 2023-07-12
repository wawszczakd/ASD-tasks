#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<int> p(n + 1);
	for (int u = 1; u <= n; u++) {
		cin >> p[u];
	}
	
	vector<int> in_deg(n + 1);
	vector<vector<int>> graph(n + 1);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		in_deg[u]++;
		graph[v].emplace_back(u);
	}
	
	priority_queue<pair<int, int>> available;
	for (int u = 1; u <= n; u++) {
		if (in_deg[u] == 0) {
			available.emplace(-p[u], u);
		}
	}
	
	int result = 0, taken = 0;
	while (!available.empty()) {
		int u = available.top().second;
		available.pop();
		
		result = max(result, p[u]);
		if (++taken >= k) {
			break;
		}
		
		for (auto v : graph[u]) {
			if (--in_deg[v] == 0) {
				available.emplace(-p[v], v);
			}
		}
	}
	cout << result << '\n';
	
	return 0;
}