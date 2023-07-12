#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 500'001, LOGN = 19;

int n;
vector<int> graph[MAXN];

int depth[2][MAXN];

void dfs_depth(int u, int parent, int d[]) {
	for (auto v : graph[u]) {
		if (v != parent) {
			d[v] = d[u] + 1;
			dfs_depth(v, u, d);
		}
	}
}

pair<int, int> find_diameter() {
	depth[0][1] = 0;
	dfs_depth(1, 0, depth[0]);
	
	int u = max_element(depth[0] + 1, depth[0] + n + 1) - depth[0];
	depth[0][u] = 0;
	dfs_depth(u, 0, depth[0]);
	
	int v = max_element(depth[0] + 1, depth[0] + n + 1) - depth[0];
	depth[1][v] = 0;
	dfs_depth(v, 0, depth[1]);
	
	return make_pair(u, v);
}

int jump_pointers[2][MAXN][LOGN];

void dfs_jump_pointers(int u, int parent, int j[][LOGN]) {
	for (int bit = 1; bit < LOGN; bit++) {
		j[u][bit] = j[j[u][bit - 1]][bit - 1];
	}
	
	for (auto v : graph[u]) {
		if (v != parent) {
			j[v][0] = u;
			dfs_jump_pointers(v, u, j);
		}
	}
}

void calculate_jump_pointers(int root0, int root1) {
	jump_pointers[0][root0][0] = root0;
	dfs_jump_pointers(root0, 0, jump_pointers[0]);
	
	jump_pointers[1][root1][0] = root1;
	dfs_jump_pointers(root1, 0, jump_pointers[1]);
}

int jump(int u, int d, int j[][LOGN]) {
	for (int bit = 0; bit < LOGN; bit++) {
		if ((d >> bit) & 1) {
			u = j[u][bit];
		}
	}
	return u;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n;
	for (int u = 1; u <= n; u++) {
		int v1, v2;
		cin >> v1 >> v2;
		if (v1 != -1) {
			graph[u].emplace_back(v1);
			graph[v1].emplace_back(u);
		}
		if (v2 != -1) {
			graph[u].emplace_back(v2);
			graph[v2].emplace_back(u);
		}
	}
	
	auto [root0, root1] = find_diameter();
	calculate_jump_pointers(root0, root1);
	
	int q;
	cin >> q;
	while (q--) {
		int u, d;
		cin >> u >> d;
		if (depth[0][u] >= d) {
			cout << jump(u, d, jump_pointers[0]) << '\n';
		}
		else if (depth[1][u] >= d) {
			cout << jump(u, d, jump_pointers[1]) << '\n';
		}
		else {
			cout << -1 << '\n';
		}
	}
	
	return 0;
}