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

// 二次元座標圧縮 O(n log n)(重め)
// (y1, x1), (y2, x2) を端点にもつ長方形
template<class T> map<T, T> compress(const vector<T>& a){
    int n = a.size();
    vector<T> b = a;
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    map<T, T> mp;
    rep(i, 0, n) mp[a[i]] = lower_bound(all(b), a[i]) - b.begin();
    return mp;
}

vector<vector<char>> compress2D(int& h, int& w, const vector<int>& y1, const vector<int>& x1, const vector<int>& y2, const vector<int>& x2){
    vector<int> y = {0, h}, x = {0, w};
    for(const auto& e : y1) y.emplace_back(e);
    for(const auto& e : y2) y.emplace_back(e);
    for(const auto& e : x1) x.emplace_back(e);
    for(const auto& e : x2) x.emplace_back(e);
    map<int, int> my = compress(y), mx = compress(x);
    h = my[h], w = mx[w];
    vector ret(h, vector(w, '.'));
    
    vector s(h + 1, vector(w + 1, 0)), t(h + 1, vector(w + 1, 0));
    int n = y1.size();
    rep(i, 0, n){
        auto [sy, sx, ty, tx] = make_tuple(y1[i], x1[i], y2[i], x2[i]);
        sy = my[sy]; sx = mx[sx]; ty = my[ty]; tx = mx[tx];
        rep(j, sx, tx) s[sy][j]++, s[ty][j]--;
        rep(i, sy, ty) t[i][sx]++, t[i][tx]--;
    }
    rep(i, 0, h){
        int sum = 0;
        rep(j, 0, w){
            sum += t[i][j];
            if(sum > 0) ret[i][j] = '#';
        }
    }
    rep(j, 0, w){
        int sum = 0;
        rep(i, 0, h){
            sum += s[i][j];
            if(sum > 0) ret[i][j] = '#';
        }
    }
    return ret;
}
