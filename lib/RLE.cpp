//ランレングス圧縮 O(n)
vector<pair<char, int>> encode(const string &str){
    int n = str.size();
    vector<pair<char, int>> ret;
    for (int l = 0; l < n;){
        int r = l + 1;
        while(r < n && str[l] == str[r]) r++;
        ret.push_back(pair<char, int>(str[l], r - l));
        l = r;
    }
    return ret;
}

//vectorバージョン
vector<pair<int, int>> encode(const vector<int> &a){
    int n = a.size();
    vector<pair<int, int>> ret;
    for (int l = 0; l < n;){
        int r = l + 1;
        while(r < n && a[l] == a[r]) r++;
        ret.push_back(pair<int, int>(a[l], r - l));
        l = r;
    }
    return ret;
}

//ランレングス圧縮の復元 O(n)
string decode(const vector<pair<char, int>> &code){
    string ret = "";
    for (auto p : code){
        for (int i = 0; i < p.second; i++){
            ret.push_back(p.first);
        }
    }
    return ret;
}