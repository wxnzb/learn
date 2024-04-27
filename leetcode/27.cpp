class Solution {
public:
    int maximum69Number (int num) {
      int cnt=0;
      vector<int>arr(4);
      int m=num;
      while(m)
      {
        arr[cnt++]=m%10;
         m/=10;
      }
      for(int i=cnt-1;i>=0;i--)
      {
        if(arr[i]==6)
        {
            num+=3*pow(10,i);
            return num;
        }
      }
      return num;
    }
};
