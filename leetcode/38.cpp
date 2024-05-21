class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n=nums.size();
       for(int i=0;i<n-1;++i)
       {
        for(int j=i+1;j<=min(i+k,n-1);j++)
        {
            if(nums[i]==nums[j])
            return 1;
        }
       }
       return 0;
    }
};
