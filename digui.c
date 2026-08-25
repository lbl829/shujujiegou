#include<stdio.h>
#include<math.h>
int Max(int* a,int n)
{
    int dp[1000];
    if(n==0)
    {
        return 0;
    }
    if(n==1)
    {
        return a[0];
    }
    dp[0]=a[0];
    dp[1]=fmax(a[0],a[1]);
    for(int i=2;i<n;i++)
    {
        dp[i]=fmax(dp[i-1],dp[i-2]+a[i]);
    }
    return dp[n-1];
}
int main()
{
    int n=5;
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
    }
    int x=Max(nums,5);
    printf("%d",x);
    return 0;
}