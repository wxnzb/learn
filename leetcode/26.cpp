class Solution {
public:
    string strWithout3a3b(int a, int b) {
      if(a==0)  return string(b,'b');
      if(b==0)  return string(a,'a');
      if(a==b)  return "ab"+strWithout3a3b(a-1,b-1);
      return a>b?"aab"+strWithout3a3b(a-2,b-1):"bba"+strWithout3a3b(a-1,b-2);  
    }
};
