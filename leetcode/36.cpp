class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
      unordered_map<int, int> p;
     for(int num:nums)
     {
       if(p.count(num))
       return true;
       else
        p[num]=2;
     }
     return false;
    }
};
