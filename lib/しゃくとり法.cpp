//配列aに対して和がk以上になる区間の総数
ll ans = 0, sum = 0;
    for(int r = 0, l = 0; l < n; l++){
        while(r < n && sum + a[r] < k) sum += a[r], r++;
        ans += n - r; //条件がk未満ならr - l
        sum -= a[l];
        /* l <= r を守る場合
        if(l == r) r++, l++;
        else sum -= a[l];
        */
    }