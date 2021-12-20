// 座標圧縮 O(n log n)

template<class T> vector<T> compress(const vector<T>& a){
    int n = a.size();
    vector<T> b = a;
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    vector<T> ret(n);
    rep(i, 0, n) ret[i] = lower_bound(all(b), a[i]) - b.begin();
    return ret;
}
