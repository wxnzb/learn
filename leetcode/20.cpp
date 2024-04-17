class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int S = s.size() - 1; 
        int result = 0;
        int G=g.size() - 1;
        for (int i = G; i >= 0; i--) { 
            if (S>=0&&s[S] >= g[i]) { 
                result++;
                S--;
            }
        }
        return result;
    }
};
