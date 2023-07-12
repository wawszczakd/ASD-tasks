#include <bits/stdc++.h>
using namespace std;

mt19937 gen(2137);
int rand_int(int l, int r) {
	return uniform_int_distribution<int>{l, r}(gen);
}

struct treap_node {
	int key, priority, value, my_size, size, lazy;
	treap_node *left, *right;
	
	treap_node() {
		key = 0;
		priority = rand_int(INT_MIN, INT_MAX);
		value = 0;
		my_size = 0;
		size = 0;
		lazy = 0;
		left = right = nullptr;
	}
	
	treap_node(int _key, int _value, int _my_size) {
		key = _key;
		priority = rand_int(INT_MIN, INT_MAX);
		value = _value;
		my_size = _my_size;
		size = _my_size;
		lazy = 0;
		left = right = nullptr;
	}
};

void propagate(treap_node *v) {
	if (v && v->lazy != 0) {
		if (v->left) {
			v->left->key += v->lazy;
			v->left->lazy += v->lazy;
		}
		if (v->right) {
			v->right->key += v->lazy;
			v->right->lazy += v->lazy;
		}
		v->lazy = 0;
	}
}

void update(treap_node *v) {
	if (v) {
		v->size = v->my_size;
		if (v->left) {
			v->size += v->left->size;
		}
		if (v->right) {
			v->size += v->right->size;
		}
	}
}

treap_node * merge(treap_node *l, treap_node *r) {
	if (!l) {
		return r;
	}
	else if (!r) {
		return l;
	}
	else if (l->priority > r->priority) {
		propagate(l);
		l->right = merge(l->right, r);
		update(l);
		return l;
	}
	else {
		propagate(r);
		r->left = merge(l, r->left);
		update(r);
		return r;
	}
}

pair<treap_node *, treap_node *> split(treap_node *v, int key) {
	if (!v) {
		return make_pair(nullptr, nullptr);
	}
	else if (v->key < key) {
		propagate(v);
		auto [l, r] = split(v->right, key);
		v->right = l;
		update(v);
		return make_pair(v, r);
	}
	else {
		propagate(v);
		auto [l, r] = split(v->left, key);
		v->left = r;
		update(v);
		return make_pair(l, v);
	}
}

treap_node * get(treap_node *v, int where) {
	propagate(v);
	int left_size = (v->left ? v->left->size : 0);
	if (left_size >= where) {
		return get(v->left, where);
	}
	else if (left_size + v->my_size >= where) {
		return v;
	}
	else {
		return get(v->right, where - (left_size + v->my_size));
	}
}

treap_node * insert(treap_node *v, int where, int value, int cnt) {
	if (!v || where > v->size) {
		return merge(v, new treap_node(where, value, cnt));
	}
	
	treap_node *node = get(v, where);	
	auto [l, r] = split(v, node->key);
	auto [rl, rr] = split(r, node->key + node->my_size);
	
	treap_node *new_node = new treap_node(where, value, cnt);
	if (node->key < where) {
		new_node = merge(new treap_node(node->key, node->value, where - node->key), new_node);
	}
	new_node = merge(new_node, new treap_node(where + cnt, node->value, node->key + node->my_size - where));
	
	if (rr) {
		rr->key += cnt;
		rr->lazy += cnt;
	}
	return merge(merge(l, new_node), rr);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	treap_node *root = nullptr;
	
	int q;
	cin >> q;
	
	int prev_result = 0, n = 0;
	while (q--) {
		char type;
		cin >> type;
		if (type == 'i') {
			int where, value, cnt;
			cin >> where >> value >> cnt;
			where = (where + prev_result) % (n + 1);
			root = insert(root, where + 1, value, cnt);
			n += cnt;
		}
		else {
			int where;
			cin >> where;
			where = (where + prev_result) % n;
			prev_result = get(root, where + 1)->value;
			cout << prev_result << '\n';
		}
	}
	
	return 0;
}