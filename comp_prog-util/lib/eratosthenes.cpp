//エラトステネスの篩 O(nloglogn)
vector<bool> eratosthenes(int n){
    vector<bool> ret(n, true);
    ret[0] = false;
    ret[1] = false;
    for(int i = 2; i * i < n; i++) if(ret[i]) for(int j = i * i; j < n; j += i) ret[j] = false;
    return ret;
}
