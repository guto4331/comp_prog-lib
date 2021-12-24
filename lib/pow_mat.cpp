// m x m 行列の n 乗を O(m^3 log n) で、mint で求める

vector<vector<mint>> pow_mat(const vector<vector<mint>>& base, vector<vector<mint>> a, ll n){
    if(n == 1) return a;
    int m = a.size();
    if(n % 2 == 1){
        vector temp = pow_mat(base, a, n - 1);
        vector ret(m, vector(m, mint(0)));
        rep(i, 0, m) rep(j, 0, m) rep(k, 0, m) ret[i][j] += temp[i][k] * base[k][j];
        return ret;
    }else{
        vector temp = pow_mat(base, a, n / 2);
        vector ret(m, vector(m, mint(0)));
        rep(i, 0, m) rep(j, 0, m) rep(k, 0, m) ret[i][j] += temp[i][k] * temp[k][j];
        return ret;
    }
}
