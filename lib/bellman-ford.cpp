// 負の閉路がないグラフ g 上の始点 s からの最短経路問題を解く (O(|V||E|))

vector<ll> bellman_ford(const Graph& g, int s){
    int n = g.size();
    vector<ll> dist(n, INF);
    dist[s] = 0;
    rep(i, 0, n){
        if(dist[i] == INF) continue;
        bool update = false;
        for(auto e : g[i]) if(chmin(dist[e.to], dist[i] + e.cost)) update = true;
        if(!update) break;
	    // contains negative cycle
        assert(!(i == n - 1 && update));
    }
    return dist;
}