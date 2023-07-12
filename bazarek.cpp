#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9 + 7;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a.begin() + 1, a.end(), greater<int>());
	
	vector<int> max_even_suff(n + 2, -1), max_odd_suff(n + 2, -1);
	for (int i = n; i >= 1; i--) {
		if (a[i] % 2 == 0) {
			max_even_suff[i] = max(max_even_suff[i + 1], a[i]);
			max_odd_suff[i] = max_odd_suff[i + 1];
		}
		else {
			max_odd_suff[i] = max(max_odd_suff[i + 1], a[i]);
			max_even_suff[i] = max_even_suff[i + 1];
		}
	}
	
	vector<long long> result(n + 1, -1);
	long long current_sum = 0;
	int min_even_pref = INF, min_odd_pref = INF;
	for (int i = 1; i <= n; i++) {
		current_sum += a[i];
		
		if (a[i] % 2 == 0) {
			min_even_pref = min(min_even_pref, a[i]);
		}
		else {
			min_odd_pref = min(min_odd_pref, a[i]);
		}
		
		if (current_sum % 2 == 1) {
			result[i] = current_sum;
		}
		else {
			if (min_even_pref != INF && max_odd_suff[i + 1] != -1) {
				result[i] = max(result[i], current_sum - min_even_pref + max_odd_suff[i + 1]);
			}
			if (min_odd_pref != INF && max_even_suff[i + 1] != -1) {
				result[i] = max(result[i], current_sum - min_odd_pref + max_even_suff[i + 1]);
			}
		}
	}
	
	int m;
	cin >> m;
	
	while (m--) {
		int k;
		cin >> k;
		
		cout << result[k] << '\n';
	}
	
	return 0;
}