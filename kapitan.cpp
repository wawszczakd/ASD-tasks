#include <bits/stdc++.h>
using namespace std;

struct point {
	int x, y, id;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	vector<point> points(n);
	for (int i = 0; i < n; i++) {
		cin >> points[i].x >> points[i].y;
		points[i].id = i;
	}
	
	vector<vector<pair<int, int>>> graph(n);
	
	sort(points.begin(), points.end(),
	[&](const point a, const point b) {
		return a.x < b.x;
	});
	for (int i = 1; i < n; i++) {
		int cost = points[i].x - points[i - 1].x;
		graph[points[i].id].emplace_back(points[i - 1].id, cost);
		graph[points[i - 1].id].emplace_back(points[i].id, cost);
	}
	
	sort(points.begin(), points.end(),
	[&](const point a, const point b) {
		return a.y < b.y;
	});
	for (int i = 1; i < n; i++) {
		int cost = points[i].y - points[i - 1].y;
		graph[points[i].id].emplace_back(points[i - 1].id, cost);
		graph[points[i - 1].id].emplace_back(points[i].id, cost);
	}
	
	vector<int> dist(n, INT_MAX);
	dist[0] = 0;
	
	priority_queue<pair<int, int>> active;
	active.emplace(0, 0);
	while (!active.empty()) {
		auto [d, u] = active.top();
		active.pop();
		d *= -1;
		
		if (d == dist[u]) {
			for (auto [v, cost] : graph[u]) {
				if (dist[u] + cost < dist[v]) {
					dist[v] = dist[u] + cost;
					active.emplace(-dist[v], v);
				}
			}
		}
	}
	
	cout << dist[n - 1] << '\n';
	
	return 0;
}