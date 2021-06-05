vector<vector<mint>> pow_det(vector<vector<mint>>& base, vector<vector<mint>> a, ll n){
    if(n == 1) return a;
    int b = a.size();
    if(n % 2 == 1){
        vector temp = pow_det(base, a, n - 1);
        vector ret(b, vector(b, mint(0)));
        rep(i, 0, b) rep(j, 0, b) rep(k, 0, b) ret[i][j] += temp[i][k] * base[k][j];
        return ret;
    }else{
        vector temp = pow_det(base, a, n / 2);
        vector ret(b, vector(b, mint(0)));
        rep(i, 0, b) rep(j, 0, b) rep(k, 0, b) ret[i][j] += temp[i][k] * temp[k][j];
        return ret;
    }
}