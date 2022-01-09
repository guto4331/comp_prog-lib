// 無向グラフ g を連結成分ごとに (頂点の集合, 辺の数) で分解する O(n + m)

vector<pair<vector<int>, int>> cc_decomp(const Graph &g){
    vector<pair<vector<int>, int>> ret;
    int n = g.size();
    vector<bool> seen(n);
    rep(i, 0, n) if(!seen[i]){
        vector<int> vs;
        int cnte = 0;
        queue<int> q;
        q.emplace(i);
        seen[i] = true;
        while(!q.empty()){
            int v = q.front(); q.pop();
            vs.emplace_back(v);
            for(const auto& u : g[v]){
                cnte++;
                if(seen[u]) continue;
                q.emplace(u);
                seen[u] = true;
            }
        }
        ret.emplace_back(vs, cnte / 2);
    }
    return ret;
}
