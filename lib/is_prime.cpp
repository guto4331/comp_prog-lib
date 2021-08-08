// 素数判定 O(√n)
bool is_prime(ll n){
    if(n == 1) return false;
    for(int i = 2; i <= sqrt(n); i++) if(n % i == 0) return false;
    return true;
}