#include<stdio.h>
void SelectionSort(int* a,int n)
{
    int i,j,mindex;
    for(i=0;i<n-1;i++)
    {
        mindex=i;
        for(j=i+1;j<n;j++)
        {
            if(a[j]<a[mindex])
            {
                mindex=j;
            }
        }
        int temp;
        temp=a[i];
        a[i]=a[mindex];
        a[mindex]=temp;
    }
    for(i=0;i<n;i++)
    {
        printf("%d",a[i]);
    }
}
int main()
{
    int n=6;
    int a[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    SelectionSort(a,6);
    return 0;
}