#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 200'001;

vector<int> children[MAXN];
int vertex_color[MAXN], pre_order[MAXN], post_order[MAXN];

void dfs(int u) {
	static int timer = 0;
	pre_order[u] = ++timer;
	for (auto v : children[u]) {
		dfs(v);
	}
	post_order[u] = timer;
}

struct segment_tree {
private:
	int base;
	vector<set<pair<int, int>>> nodes;
	
public:
	segment_tree() {
		base = 0;
		nodes.clear();
	}
	
	segment_tree(int n) {
		base = 1;
		while (base < n) {
			base <<= 1;
		}
		nodes.clear();
		nodes.resize(base << 1);
	}
	
	void insert(int i, int color) {
		for (i += base; i > 0; i >>= 1) {
			int cnt = 1;
			set<pair<int,int>>::iterator it = nodes[i].lower_bound(make_pair(color, 0));
			if (it != nodes[i].end() && it->first == color) {
				cnt += it->second;
				nodes[i].erase(it);
			}
			nodes[i].insert(make_pair(color, cnt));
		}
	}
	
	void erase(int i, int color) {
		for (i += base; i > 0; i >>= 1) {
			set<pair<int,int>>::iterator it = nodes[i].lower_bound(make_pair(color, 0));
			int cnt = it->second - 1;
			nodes[i].erase(it);
			if (cnt > 0) {
				nodes[i].insert(make_pair(color, cnt));
			}
		}
	}
	
	bool query(int l, int r) {
		set<pair<int, int>> interval;
		for (l += base, r += base + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) {
				for (auto [color, cnt] : nodes[l]) {
					set<pair<int, int>>::iterator it = interval.lower_bound(make_pair(color, 0));
					if (it != interval.end() && it->first == color) {
						cnt += it->second;
						interval.erase(it);
					}
					interval.insert(make_pair(color, cnt));
					if ((int) interval.size() > 2) {
						return false;
					}
				}
				l++;
			}
			if (r & 1) {
				r--;
				for (auto [color, cnt] : nodes[r]) {
					set<pair<int, int>>::iterator it = interval.lower_bound(make_pair(color, 0));
					if (it != interval.end() && it->first == color) {
						cnt += it->second;
						interval.erase(it);
					}
					interval.insert(make_pair(color, cnt));
					if ((int) interval.size() > 2) {
						return false;
					}
				}
			}
		}
		if ((int) interval.size() == 1) {
			return true;
		}
		else {
			return (interval.begin()->second == 1 || next(interval.begin())->second == 1);
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, q;
	cin >> n >> q;
	for (int u = 2; u <= n; u++) {
		int parent;
		cin >> parent;
		children[parent].emplace_back(u);
	}
	for (int u = 1; u <= n; u++) {
		cin >> vertex_color[u];
	}
	
	dfs(1);
	
	segment_tree tree(n + 1);
	for (int u = 1; u <= n; u++) {
		tree.insert(pre_order[u], vertex_color[u]);
	}
	
	while (q--) {
		char type;
		cin >> type;
		if (type == '?') {
			int u;
			cin >> u;
			cout << (tree.query(pre_order[u], post_order[u]) ? "TAK" : "NIE") << '\n';
		}
		else {
			int u, color;
			cin >> u >> color;
			tree.erase(pre_order[u], vertex_color[u]);
			vertex_color[u] = color;
			tree.insert(pre_order[u], vertex_color[u]);
		}
	}
	
	return 0;
}