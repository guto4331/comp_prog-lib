//高速べき乗 O(logn)
ll mod_pow(ll x, ll n){
    if(n == 0) return 1;
    ll ret = mod_pow(x * x % MOD, n / 2);
    if((n & 1) == 1) ret = ret * x % MOD + MOD;
    return ret;
}