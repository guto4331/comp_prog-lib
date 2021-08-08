// 全点対最短経路問題を解く O(V^3)
rep(k, 0, 10) rep(i, 0, 10) rep(j, 0, 10) chmin(dist[i][j], dist[i][k] + dist[k][j]);