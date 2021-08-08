// 閉路を含まない有向グラフ g に対してトポロジカルソートをする (O(|V| + |E|))

vector<int> topological_sort(const Graph& g){
    vector<int> ret;
    int n = g.size();
    vector<int> cnt_in(n);
    rep(i, 0, n){
        for(const auto& v : g[i]) cnt_in[v]++;
    }
    queue<int> q;
    rep(i, 0, n) if(cnt_in[i] == 0) q.emplace(i);
    while(!q.empty()){
        int v = q.front(); q.pop();
        ret.emplace_back(v);
        for(const auto& u : g[v]){
            cnt_in[u]--;
            if(cnt_in[u] == 0) q.emplace(u);
        }
    }
    return ret;
}