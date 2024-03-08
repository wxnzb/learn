int candy(int* ratings, int ratingsSize) {
    int dp[ratingsSize];
    dp[0]=1;
    for(int i=1;i<ratingsSize;i++)
    {
        if(ratings[i]>ratings[i-1])
        dp[i]=dp[i-1]+1;
        else
        dp[i]=1;
    }
    for(int i=ratingsSize-2;i>=0;i--)//212
    {
        if(ratings[i]>ratings[i+1]&&dp[i]<=dp[i+1])
        dp[i]=dp[i+1]+1;
    }
    int sum=0;
    for(int i=0;i<ratingsSize;i++)
    sum+=dp[i];
    return sum;
}
