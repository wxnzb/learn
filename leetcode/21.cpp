class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
       int n=row.size()/2;
       int p[n];
       iota(p,p+n,0);
       function<int(int)>find=[&](int x)->int{
        if(x!=p[x])
        x=find(p[x]);
        return x;
       };
       for(int i=0;i<n<<1;i+=2)
       {
        int a=row[i]>>1;
        int b=row[i+1]>>1;
        p[find(a)]=find(b);
       }
       int cnt=0;
       for(int i=0;i<n;i++)
       {
           if(i==p[i])
           cnt++;
       }
       return n-cnt;
    }
};
