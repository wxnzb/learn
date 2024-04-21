class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
       int s=accumulate(nums.begin(),nums.end(),0);
       if(s%3==0)
       return s;
       vector<int>a[3];
       for(int x:nums)
       {
        a[x%3].push_back(x);
       }
       sort(a[1].begin(),a[1].end());
       sort(a[2].begin(),a[2].end());
        if (s % 3 == 2)
            swap(a[1], a[2]);
        int ans = a[1].size() ? s - a[1][0] : 0;
        if (a[2].size() > 1)
            ans = max(ans, s - a[2][0] - a[2][1]);
        return ans;
    }
};

