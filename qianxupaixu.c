#include<stdio.h>
int n;
int post[35];
int in[35];
int first=1;
void build(int a,int b,int c,int d)    /*a,b是后序排序的最左下标和最右下标，c,d是中序排序的最左下标和最右下标*/
{
    if(a>b)
    {
        return;
    }
    if(c>d)
    {
        return;
    }
    int root=post[b];
    int p;
    for(int i=c;i<=d;i++)
    {
        if(in[i]==root)
        {
            p=i;
            break;
        }
    }
    int x=p-c;
    if(first==1)
    {
        printf("%d",root);
        first=0;
    }
    else
    {
        printf(" %d",root);
    }
    build(a,a+x-1,c,p-1);
    build(a+x,b-1,p+1,d);
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&post[i]);
    }
    for(int i=0;i<n;i++)
    {
        scanf("%d",&in[i]);
    }
    printf("Postorder: ");
    build(0,n-1,0,n-1);
    printf("\n");
    return 0;
}
