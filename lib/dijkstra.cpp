// 負の重みの辺がないグラフ g 上の始点 s からの最短経路問題を解く (O(|E| log |V|))

vector<ll> dijkstra(const Graph &g, int s){
    int n = g.size();
    vector<ll> dist(n, INF * INF);
    dist[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.emplace(dist[s], s);
    while(q.size()){
        pair<ll, int> p = q.top(); q.pop();
        int v = p.second;
        if(dist[v] < p.first) continue;
        for(auto e : g[v]){
            if(chmin(dist[e.to], dist[v] + e.cost)) q.emplace(dist[e.to], e.to);
        }
    }
    return dist;
}