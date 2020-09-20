// OBS: s1.length() < s2.length()
int LCS(string s1, string s2) {
    vector<int> p[130];
    for(int i = 0; i < s2.size() ; ++i) {
        char index = s2[i];
        p[index].push_back(i);
    }

    vector<int> v;
    v.push_back(-1);

    for(int i = 0; i < s1.size(); ++i) {
        char index = s1[i];
        for(int j = p[index].size() - 1 ; j >= 0 ; --j) {
            int n = p[index][j];

            if (n > v.back()) v.push_back(n);
            else *lower_bound(v.begin(), v.end(), n) = n;
        }
    }
    return v.size() - 1;
}:
