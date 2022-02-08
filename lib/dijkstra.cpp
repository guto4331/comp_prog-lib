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

// 拡張ダイクストラ　情報を多くもつ必要があるとき

typedef struct info{
    ll dist; int from, cur;
    info(ll dist, int from, int cur) : dist(dist), from(from), cur(cur) {}
}info_t;

vector dist(n, vector(n, INF * INF));
priority_queue<info_t, vector<info_t>, greater<info_t>> q;
rep(i, 0, n){
    dist[i][0] = 0;
}
q.emplace(0, -1, 0);
while(!q.empty()){
    auto [c, prev, cur] = q.top(); q.pop();
    if(prev != -1 && dist[prev][cur] < c) continue;
    for(const auto& e : g[cur]){
        if(prev != -1 && /* 条件 */) continue;
        if(chmin(dist[cur][e.to], c + e.cost)) q.emplace(dist[cur][e.to], cur, e.to);
    }
}

ll ans = INF * INF;
rep(i, 0, n) chmin(ans, dist[i][1]);
cout << (ans == INF * INF ? -1 : ans) << endl;
