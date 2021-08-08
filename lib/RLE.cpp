// ランレングス圧縮 O(n)
vector<pair<char, int>> encode(const string& str){
    int n = str.size();
    vector<pair<char, int>> ret;
    for (int l = 0; l < n;){
        int r = l + 1;
        while(r < n && str[l] == str[r]) r++;
        ret.emplace_back(pair<char, int>(str[l], r - l));
        l = r;
    }
    return ret;
}

// vectorバージョン
vector<pair<int, int>> encode(const vector<int>& v){
    int n = v.size();
    vector<pair<int, int>> ret;
    for (int l = 0; l < n;){
        int r = l + 1;
        while(r < n && v[l] == v[r]) r++;
        ret.emplace_back(pair<int, int>(v[l], r - l));
        l = r;
    }
    return ret;
}

// ランレングス圧縮の復元 O(n)
string decode(const vector<pair<char, int>>& code){
    string ret = "";
    for (const auto& p : code){
        for (int i = 0; i < p.second; i++){
            ret.emplace_back(p.first);
        }
    }
    return ret;
}