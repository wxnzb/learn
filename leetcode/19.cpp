class Solution {
public:
    int jump(vector<int>& nums) {
        if(nums.size()==1)return 0;
      int result=0;
      int cur=0;
      int next=0;
      for(int i=0;i<nums.size();i++)
      {
        next=max(next,i+nums[i]);
        if(i==cur)
        {
            result++;
            cur=next;
            if(cur>=nums.size()-1)
            return result;
        }
      }
      return result;
    }
};
