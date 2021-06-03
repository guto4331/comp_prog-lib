//サイズ n の配列 a について、任意の区間の最大公約数を求める。 O(n log n)

int op(int a, int b) { return gcd(a, b); }
int e(){ return 0; }

segtree<int, op, e> seg(n);
rep(i, 0, n) seg.set(i, a[i]);

//seg.prod(l, r) で gcd(a[l], a[l + 1], ... , a[r - 1]) を求める