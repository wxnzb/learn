class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
          if(digits.empty()) {
            digits.push_back(1);
            return digits;
        }
        int m=digits.back();
        digits.pop_back();
       if(m<9)
       {
         digits.push_back(m+1);
         return digits;
       }
        else
        {
            plusOne(digits);
            digits.push_back(0);
        }
        return digits;
    }
};
