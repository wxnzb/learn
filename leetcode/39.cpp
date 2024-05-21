class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        int k=indexDiff;
        int t=valueDiff;
        int n=nums.size();
        set<int>rec;
        for(int i=0;i<n;i++)
        {
            auto it=rec.lower_bound(max(nums[i],INT_MIN+t)-t);
            if(it!=rec.end() && *it<=min(nums[i],INT_MAX-t)+t)
            return 1;
           rec.insert(nums[i]);
            if(i>=k)
            {
                rec.erase(nums[i-k]);
            }
        }
        return 0;
    }
};
