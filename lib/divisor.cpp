// 高速な約数全列挙 O(√n)
vector<ll> divisor(ll n){
    vector<ll> ret;
    for(ll i = 1; i * i <= n; i++){
        if (n % i == 0) {
            ret.emplace_back(i);
            if (i * i != n) ret.emplace_back(n / i);
        }
    }
    return ret;
}