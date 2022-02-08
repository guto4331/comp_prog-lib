// 配列をソートした後の idx の対応順を返す O(n log n)

template<class T> vector<T> sort_order(const vector<T>& a){
    int n = a.size();
    vector<pair<int, int>> b(n);
    rep(i, 0, n) b[i] = { a[i], i };
    sort(all(b));
    vector<int> ret(n);
    rep(i, 0, n) ret[i] = b[i].second;
    return ret;
}
