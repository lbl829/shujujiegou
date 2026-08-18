#include<stdio.h>
void twosum(int * a,int n,int target)
{
    for(int  i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(a[i]+a[j]==target)
            {
                printf("%d %d\n",i,j);
            }
        }
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    int  a[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    int target;
    scanf("%d",&target);
    twosum(a,n,target);
    return 0;
}