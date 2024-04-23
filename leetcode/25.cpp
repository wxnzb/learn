class Solution {
    string A[10]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
public:
    vector<string> letterCombinations(string digits) {
       int n=digits.length();
       if(n==0)
       return{};
        vector<string>ans;
        string path(n,0);
       function<void(int)>dfs=[&](int i)
       {
        if(i==n)
        return ans.push_back(path);
        for(char c:A[digits[i]-'0'])
        {
          path[i]=c;
          dfs(i+1);
        }
       };
       dfs(0);
       return ans;
    }
};
