#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define all(v) v.begin(), v.end()
#define rep(i, begin, end) for(auto i = (begin); i < (end); i++)
#define rrep(i, end, begin) for(auto i = (end) - 1; i >= (begin); i--)
template<class T> inline bool chmin(T& a, T b){ if (a > b){ a = b; return true; } return false; }
template<class T> inline bool chmax(T& a, T b){ if (a < b){ a = b; return true; } return false; }
template<class T> inline T roundup(T a, T b){ return (a + b - 1) / b; }
constexpr int dy[] = {0, 1, 0, -1, 1, 1, -1, -1, 0};
constexpr int dx[] = {1, 0, -1, 0, 1, -1, 1, -1, 0};
using ll = long long;
constexpr ll INF = 1e9;
/* #include <atcoder/all>
using namespace atcoder;
using mint = modint1000000007;
ostream& operator<<(ostream& os, const mint& n){ os << n.val(); return os; }
istream& operator>>(istream& is, mint& n){ ll m; is >> m; n = m; return is; } */
struct Edge{ int to; ll cost; Edge(int to, ll cost) : to(to), cost(cost) {} };
using Graph = vector<vector<int>>;

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    
}
