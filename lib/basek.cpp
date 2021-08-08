// k 進法の整数 n を 10 進法に変換する O(log n)
ll basek_toll(const string& n, int k){
    ll ret = 0, num = 1;
    for(int i = n.size() - 1; i >= 0; i--){
        ret += ll(n[i] - '0') * num;
        num *= k;
    }
    return ret;
}

// 10 進法の整数 n を k 進法に変換する O(log n)
string to_basek(ll n, int k){
    string ret = "";
    while(n > 0){
        ret = char(n % k + '0') + ret;
        n /= k;
    }
    return ret;
}
