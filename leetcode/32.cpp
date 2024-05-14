class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;
        unordered_map<int, int> count;
        
        for(int num : nums) {
            count[num]++;
        }
        
        for(auto it : count) {
            if(it.second > n/3) {
                result.push_back(it.first);
            }
        }
        
        return result;
    }
};
