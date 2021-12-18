#include "baitap7.h"
#include "bns.h"

long bn_xdist(bn_tree_t t, bn_node_t n) {
	long x = 0;
	bn_node_t cur = n;
	if (n == t->root) {
		return x;
	}
	for (;;) {
		if (cur == cur->top->left) {
			x = x - 1;
		} else {
			x = x + 1;
		}
		cur = cur->top;
		if(cur == t->root) break;
	}
	return x;
}

int bn_is_bns(bn_tree_t t) {
	bn_traverse_lnr(cur, t) {
		if(t->root->left == NULL && t->root->right == NULL) {
			return 1;
		}
		if (cur != t->root) {
			if (cur == cur->top->left) {
				if (bns_tree_g_cmp(t)(bns_node_g_key(cur), bns_node_g_key(cur->top)) > 0) {
					return 0;
				}
			} else {
				if (bns_tree_g_cmp(t)(bns_node_g_key(cur->top), bns_node_g_key(cur)) > 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}

bn_node_t bn_lca(bn_node_t n1, bn_node_t n2) {
	bn_node_t lca;
	if (n1->top == NULL || n2->top == NULL) {
		lca = NULL;
		return lca;
	}
	if (n1->top == n2->top)	{
		lca = n1->top;
		return lca;
	}
	if (bn_distance(n1) > bn_distance(n2)) {
		bn_lca(n1->top, n2);
	} else {
		bn_lca(n1, n2->top);
	}
}

void arr_to_bns(bn_tree_t t, int *a, int begin, int end) {
	if (begin > end) return;
	bns_insert_g(t, (gtype){.i = a[(begin + end)/2]});
	arr_to_bns(t, a, begin, (begin + end)/2 - 1);
	arr_to_bns(t, a, (begin + end)/2 + 1, end);	
}

bn_tree_t bns_parse_arri(int *a, size_t n) {
	bn_tree_t t = bns_create_tree_g(NULL, gtype_cmp_i);
	arr_to_bns(t, a, 0, n-1);
	return t;
}