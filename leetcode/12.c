int nthUglyNumber(int n) {
    //动态规划
     int *dp=(int*)malloc(sizeof(int)*(n+1));
    dp[1]=1;
    int dp1=1;
    int dp2=1;
    int dp3=1;
    for(int i=2;i<n+1;i++)
    {
         int num1=dp[dp1]*2;
         int num2=dp[dp2]*3;
         int num3=dp[dp3]*5;
        dp[i]=num1>num2?(num2>num3?num3:num2):(num1>num3?num3:num1);
        if(dp[i]==num1)
        dp1++;
        if(dp[i]==num2)
        dp2++;
        if(dp[i]==num3)
        dp3++;
    }
    return dp[n];
}
