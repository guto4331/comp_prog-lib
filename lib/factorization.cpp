// 素因数分解 O(√n)
vector<ll> factorization(ll n){
    vector<ll> ret;
    for(ll i = 2; i * i <= n; i++){
        while(n % i == 0) ret.emplace_back(i), n /= i;
    }
    if(n != 1) ret.emplace_back(n);
    return ret;
}


// 前処理がある素因数分解(osa_k 法) 前処理 O(n log log n), クエリ毎に O(log n)
vector<int> min_factor(int n){
    vector<int> ret(n, n + 1);
    for(int i = 2; i * i < n; i++){
        if(ret[i] < i) continue;
        for(int j = i * i; j < n; j += i) chmin(ret[j], i);
    }
    rep(i, 0, n) if(ret[i] == n + 1) ret[i] = i;
    ret[0] = -1, ret[1] = -1;
    return ret;
}

vector<int> factorization(int n, const vector<int>& v){
    vector<int> ret;
    while(n > 1){
        ret.emplace_back(v[n]);
        n /= v[n];
    }
    return ret;
}