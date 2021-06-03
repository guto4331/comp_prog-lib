//二分探索(上限n, 下限0, 条件C) 計算量O(logn)
int binary_search(int key){
    int left = -1;
    int right = (int)a.size();
    
    while (right - left > 1){
        int mid = left + (right - left) / 2;

        if (isOK(mid, key)) right = mid;
        else left = mid;
    }
    
    return right;
}