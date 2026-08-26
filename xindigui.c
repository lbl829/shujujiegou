#include<stdio.h>
void Max(int* a,int n)
{
    if(n==0)
    {
        printf("NULL");
    }
    if(n==1)
    {
        printf("%d",a[0]);
    }
    int x=a[0];
    int y;
    if(a[0]<a[1])
    {
        y=a[1];
    }
    else{
        y=a[0];
    }
    for(int i=2;i<n;i++)
    {
        int cur;
        if(x+a[i]<y)
        {
            cur=y;
        }
        else{
            cur=x+a[i];
        }
        x=y;
        y=cur;
    }
    printf("%d",y);
}
int main()
{
    int n=5;
    int nums[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&nums[i]);
    }
    Max(nums,5);
    return 0;
}