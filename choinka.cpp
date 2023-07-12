#include <bits/stdc++.h>
using namespace std;

int read_int() {
	char c = getchar_unlocked();
	while (!('0' <= c && c <= '9')) {
		c = getchar_unlocked();
	}
	int result = 0;
	do {
		result = result * 10 + (c - '0');
		c = getchar_unlocked();
	} while ('0' <= c && c <= '9');
	return result;
}

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

constexpr int BASE = 1 << 18;

set<pair<int, int>> nodes[BASE << 1];

void insert(int i, int color) {
	for (i += BASE; i > 0; i >>= 1) {
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
	for (i += BASE; i > 0; i >>= 1) {
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
	for (l += BASE, r += BASE + 1; l < r; l >>= 1, r >>= 1) {
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

int main() {
	int n = read_int(), q = read_int();
	for (int u = 2; u <= n; u++) {
		int parent = read_int();
		children[parent].emplace_back(u);
	}
	for (int u = 1; u <= n; u++) {
		vertex_color[u] = read_int();
	}
	
	dfs(1);
	
	for (int u = 1; u <= n; u++) {
		insert(pre_order[u], vertex_color[u]);
	}
	
	while (q--) {
		char type = getchar_unlocked();
		if (type == '?') {
			int u = read_int();
			if (query(pre_order[u], post_order[u])) {
				putchar_unlocked('T');
				putchar_unlocked('A');
				putchar_unlocked('K');
			}
			else {
				putchar_unlocked('N');
				putchar_unlocked('I');
				putchar_unlocked('E');
			}
			putchar_unlocked('\n');
		}
		else {
			int u = read_int(), color = read_int();
			erase(pre_order[u], vertex_color[u]);
			vertex_color[u] = color;
			insert(pre_order[u], vertex_color[u]);
		}
	}
	
	return 0;
}