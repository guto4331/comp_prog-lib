// 最小全域木問題を解く 計算量 O(E log V)

ll prim(const Graph& g){
    ll ret = 0;
    vector<bool> used(n);
    vector<int> min_cost(n);
    priority_queue<P, vector<P>, greater<P>> q;
    q.emplace(0, 0);
    while(!q.empty()){
        auto [cur, v] = q.top(); q.pop();
        if(used[v]) continue;
        used[v] = true;
        ret += cur;
        for(auto&& e : g[v]){
            if(!used[e.to]) q.emplace(e.cost, e.to);
        }
    }
    return ret;
}