#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
template<class T> bool chmin(T& a, T b){ if (a > b){ a = b; return true; } return false; }
const double INF = 1e9;
using Graph = vector<vector<int>>;
// dist: 現時点での最小コスト, from: 1 つ前の頂点, cur: 今の頂点
typedef struct info{
    double dist; int from, cur;
    info(double dist, int from, int cur) : dist(dist), from(from), cur(cur) {}
}info_t;
bool operator >(info_t a, info_t b){
    return a.dist > b.dist;
};

namespace geometry2d{
    const double EPS = 1e-10;
    int sgn(const double a){
        if(abs(a) < EPS) return 0;
        else if(a < -EPS) return -1;
        else return 1;
    }
    struct Point{
        double x, y;
        Point(double x = 0.0, double y = 0.0) : x(x), y(y) {};
        bool operator ==(Point other) const{ return (x == other.x && y == other.y); }
        Point operator +(const Point& other) const{ return { x + other.x, y + other.y }; }
        Point operator -(const Point& other) const{ return { x - other.x, y - other.y }; }
        Point operator *(double k) const{ return { x * k, y * k }; }
        bool isZero(){ return (x == 0 && y == 0); }
        double dot(Point other) const{ return x * other.x + y * other.y; }
        double cross(Point other) const{ return x * other.y - y * other.x; }
    };
    const Point error_val = { 1e5, 1e5 };
    double dot(Point a, Point b){ return a.x * b.x + a.y * b.y; }
    double cross(Point a, Point b){ return a.x * b.y - a.y * b.x; }
    /*
        name: judge_turn_type
        description: 3 点の位置関係を求める
        args: a, b, c - 3 点
        return: 
            AB から見て BC は左に曲がるのなら +1
            AB から見て BC は右に曲がるのなら -1
            ABC の順番で一直線上に並ぶなら +2
            ACB の順番で一直線上に並ぶなら 0
            BAC の順番で一直線上に並ぶなら -2
    */
    int judge_turn_type(const Point& a, const Point& b, const Point& c){
        if(a == c || b == c) return 0;
	    double crval = (b - a).cross(c - b);
        if(crval > 0) return 1;
        else if(crval < 0) return -1;
        else{
            if((a - b).dot(c - b) < 0) return 2;
            else if((a - c).dot(b - c) < 0) return 0;
            else return -2;
        }
    }
    
    struct Line{
        Point from, to;
        Line(Point from, Point to) : from(from), to(to) {} ;
        Point toVec() const{
            return to - from;
        }
    };
    struct Segment : Line{
        Segment(Point a, Point b) : Line(a, b) {}
    };
	bool isParallel(Line a, Line b){
		return sgn(a.toVec().cross(b.toVec())) == 0;
	}
	// 垂直かどうか
    bool isOrthogonal(Line a, Line b){
		return sgn(a.toVec().dot(b.toVec())) == 0;
	}
    pair<bool, Point> lineIntersection(Line a, Line b){
        if(isParallel(a, b)) return { false, error_val };
        Point ret = b.from + b.toVec() * (a.toVec().cross(a.to - b.from) / a.toVec().cross(b.toVec()));
        return { true, ret };
    }
    pair<bool, Point> segmentIntersection(Segment a, Segment b){
        if(judge_turn_type(a.from, a.to, b.from) * judge_turn_type(a.from, a.to, b.to) <= 0 && judge_turn_type(b.from, b.to, a.from) * judge_turn_type(b.from, b.to, a.to) <= 0){
            if(isParallel(a, b)) return { true, error_val };
            else return lineIntersection(a, b);
        }else return { false, error_val };
    }
}
using namespace geometry2d;

// Disjoint Set Union
struct dsu{
    public:
        dsu() : _n(0){}
        explicit dsu(int n) : _n(n), parent_or_size(n, -1){}

        int merge(int a, int b){
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = leader(a), y = leader(b);
            if (x == y) return x;
            if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
            parent_or_size[x] += parent_or_size[y];
            parent_or_size[y] = x;
            return x;
        }

    bool same(int a, int b){
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a){
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a){
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    vector<vector<int>> groups(){
        vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++){
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(_n);
        for (int i = 0; i < _n; i++){
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++){
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            remove_if(result.begin(), result.end(),
                           [&](const vector<int>& v){ return v.empty(); }),
            result.end());
        return result;
    }

    private:
        int _n;
        // root node: -1 * component size
        // otherwise: parent
        vector<int> parent_or_size;
};

// 右折一回にかかるコスト
const double right_turn_cost = 10.0;
// 時間制限
const double TIME_LIMIT = 5.0 * CLOCKS_PER_SEC;
// 開始時間
const int start = clock();
// 頂点の座標
vector<Point> nodes;
// 辺の情報
vector<pair<int, int>> edges;
// 乱数生成器
random_device rnd;
mt19937 mt(rnd());
uniform_int_distribution<> rnd_node(0, (int)1e5), rnd_edge(0, (int)1e9), rnd_type(0, 1);
uniform_real_distribution<> rnd_temp(0, 1);
// 出力
vector<vector<pair<int, int>>> output;

/*
    name: get_dist,
    description: 2 点間の直線距離を求める
    args: s, t - 2 点
    return: 距離
*/
double get_dist(Point s, Point t){
    return sqrt(pow(s.x - t.x, 2) + pow(s.y - t.y, 2));
}

/*
    name: m_vector_rad
    description: prev->cur と cur->next のなす角を求める
    args: prev, cur, next - 3 点
    return: なす角 [rad]
*/
double m_vector_rad(Point prev, Point cur, Point next){
    Point a = cur - prev, b = next - cur;
    return acos(dot(a, b));
}

/*
    name: dijkstra
    description: ある頂点からほかのすべての頂点への最小コストを求める
    args: g - 探索するグラフ、s - 始点、route - 経路復元かどうか
    return:
        route == false - s から各点への最小コスト
        route == true - s から各点に遷移するときの 1 つ前の頂点の配列
*/
vector<double> dijkstra(const Graph &g, int s, bool route = false){
    int n = g.size();
    vector<double> cost(n, INF);
    cost[s] = 0;
    vector<double> prev_rec(n, -1);
    priority_queue<info_t, vector<info_t>, greater<info_t>> q;
    q.emplace(cost[s], -1, s);
    while(!q.empty()){
        auto [cur_cost, prev, cur] = q.top(); q.pop();
        // 現時点でより良いコストが求まっていたら continue
        if(cost[cur] < cur_cost) continue;
        // 次の頂点へのコストを更新する
        int add_pos;
        double max_rad = 0;
        vector<pair<double, int>> move;
        for(const auto& next : g[cur]){
            double new_cost = cur_cost + get_dist(nodes[cur], nodes[next]);
            // 一番角度がきつい道路のみ右折判定
            if(prev != -1 && judge_turn_type(nodes[prev], nodes[cur], nodes[next]) == -1){
                double cur_rad = m_vector_rad(nodes[prev], nodes[cur], nodes[next]);
                if(max_rad < cur_rad) add_pos = next, max_rad = cur_rad;
            }
            move.emplace_back(new_cost, next);
        }
        for(auto&& [tmp_cost, tmp_next] : move){
            // 頂点 cur の次数が 3 以上でないと右折にコストはかからない
            if(g[cur].size() >= 3 && max_rad != 0 && add_pos == tmp_next){
                tmp_cost += right_turn_cost;
            }
            if(chmin(cost[tmp_next], tmp_cost)){
                prev_rec[tmp_next] = cur;
                q.emplace(cost[tmp_next], cur, tmp_next);
            }
        }
    }
    if(route) return prev_rec;
    return cost;
}

/*
    name: evaluate
    description: グラフの評価値を求める
    args: g - 評価するグラフ
    return: 評価値
*/
double evaluate(const Graph &g){
    int n = g.size();
    // cost[i][j] := 2 点 i, j 間の最小コスト
    vector cost(n, vector(n, INF));
    for(int s = 0; s < n; s++){
        cost[s] = dijkstra(g, s);
    }
    double score = 0;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            score += cost[i][j];
        }
    }
    return score;
}

/*
    name: modify
    description: グラフの近傍をとる
    args: g - 操作するグラフ
    return:
        新たな辺の情報とグラフの pair
        変更されなかった場合ともに空の pair
*/
pair<vector<pair<int, int>>, Graph> modify(Graph g){
    int n = g.size();
    vector<pair<int, int>> new_edges = edges;
    int t = rnd_type(mt);
    if(t == 0){
        // 新たな辺を追加
        int u = rnd_node(mt) % n, v = rnd_node(mt) % n;
        if(u != v && g[u].size() <= 3 && find(g[u].begin(), g[u].end(), v) == g[u].end()
            && g[v].size() <= 3 && find(g[v].begin(), g[v].end(), u) == g[v].end()){
            bool ok = true;
            for(const auto& [from, to] : edges){
                if(segmentIntersection(Segment(nodes[from], nodes[to]), Segment(nodes[u], nodes[v])).first){
                    ok = false;
                }
            }
            if(ok){
                new_edges.emplace_back(u, v);
                g[u].emplace_back(v);
                g[v].emplace_back(u);
                return make_pair(new_edges, g);
            }
        }
    }else{
        // 既存の辺を削除
        if(new_edges.size() > 0){
            int idx = rnd_edge(mt) % new_edges.size();
            dsu check(n);
            for(int i = 0; i < (int)new_edges.size(); i++){
                if(i != idx) check.merge(new_edges[i].first, new_edges[i].second);
            }
            if(check.groups().size() == 1){
                auto [u, v] = new_edges[idx];
                if(find(g[u].begin(), g[u].end(), v) != g[u].end() && find(g[v].begin(), g[v].end(), v) != g[v].end() &&
                    g[u].size() > 1 && g[v].size() > 1){
                        new_edges.erase(new_edges.begin() + idx);
                        g[u].erase(find(g[u].begin(), g[u].end(), v));
                        g[v].erase(find(g[v].begin(), g[v].end(), u));
                        return make_pair(new_edges, g);
                }
            }
        }
    }
    return make_pair(vector<pair<int, int>>{}, Graph{});
}

/*
    name: optimize
    description: グラフの最適化を行う
    arg: res - 最適化するグラフ
    return: 最適化後の結果
*/
Graph optimize(Graph res){
    const double start_temp = 10000, end_temp = 1;
    while(true){
        double now = clock();
        if(now - start > TIME_LIMIT) break;
        auto [new_edges, new_graph] = modify(res);
        // invalid な操作が行われたら更新しない
        if(new_edges.size() == 0) continue;
        // 焼き鈍し法の遷移
        double prev_score = evaluate(res), new_score = evaluate(new_graph);
        double temp = start_temp + (end_temp - start_temp) * (now - start) / TIME_LIMIT;
        double prob = exp((prev_score - new_score) / temp);
        if(prob > rnd_temp(mt) || new_score < prev_score){
            res = new_graph;
            edges = new_edges;
            output.emplace_back(edges);
        }
    }
    return res;
}

/*
    name: init
    description: 初期解を構成する
    args: init_graph - n 頂点のみで構成されたグラフ
    return: 初期解と初期解の評価値の pair
*/
pair<Graph, double> init(int n){
    Graph init_graph(n);
    vector<bool> used(n);
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> q;
    q.emplace(0, pair<int, int>{-1, 0});
    while(!q.empty()){
        auto [prev, v] = q.top().second; q.pop();
        if(used[v]) continue;
        if(prev != -1){
            edges.emplace_back(prev, v);
            init_graph[prev].emplace_back(v);
            init_graph[v].emplace_back(prev);
            used[prev] = true;
        }
        used[v] = true;
        for(int u = 0; u < n; u++){
            // まだ選んでない && つなげた後の次数が 4 以下
            if(!used[u] && init_graph[u].size() < 3 && init_graph[v].size() < 3){
                q.emplace(get_dist(nodes[v], nodes[u]), pair<int, int>{v, u});
            }
        }
    }
    return make_pair(init_graph, evaluate(init_graph));
}

/*
    name: get_path
    description: 最短経路を復元する
    args: prev - dijkstra で得られた配列、t - 終点
    return: t への最短経路
*/
vector<int> get_path(const vector<int> &prev, int t) {
    vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur]){
        path.emplace_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(2);
    
    // 入力
    int n, vis;
    cin >> n >> vis;
    nodes.resize(n);
    for(auto&& node : nodes){
        double x, y;
        cin >> x >> y;
        node = { x, y };
    }
    
    auto [init_graph, init_score] = init(n);
    Graph final_graph = optimize(init_graph);
    // 出力
    cout << vis << endl;
    cout << n << endl;
    for(const auto& [x, y] : nodes) cout << "(" << (int)x << ", " << (int)y << ")" << endl;
    cout << output.size() << endl;
    for(const auto& edge : output){
        cout << edge.size() << endl;
        for(const auto& [u, v] : edge) cout << "(" << u << ", " << v << ")" << endl;
    }
    cout << "(" << init_score << ", " << evaluate(final_graph) << ")" << endl;
    
    if(vis){
        // 全点対
        for(int s = 0; s < n; s++) for(int t = 0; t < n; t++){
            vector<int> v;
            for(const auto& e : dijkstra(final_graph, s, true)) v.emplace_back((int)e);
            vector<int> temp = get_path(v, t);
            cout << temp.size() << endl;
            for(const auto& e : temp) cout << e << endl;
        }
    }
}
