// 全点対最短経路問題を解く O(n^3)
rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) chmin(dist[i][j], dist[i][k] + dist[k][j]);
