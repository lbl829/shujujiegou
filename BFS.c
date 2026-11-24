#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1005
typedef struct sequeue
{
    int data[MAX];
    int rear,front;
}sequeue;
typedef struct
{
    int vertex[MAX];
    int edge[MAX][MAX];
}juzhen;
void initsequeue(sequeue* p)
{
    p->rear=p->front=0;
}
void Push(sequeue* p,int c)
{
    p->data[p->rear]=c;
    p->rear=(p->rear+1)%MAX;
}
int POP(sequeue* p)
{
    int x=p->data[p->front];
    p->front=(p->front+1)%MAX;
    return x;
}
int isempty(sequeue* p)
{
    return p->rear==p->front;
}
void creatadj(juzhen* L,int N,int M)
{
    int i,j;
    for(i=1;i<=N;i++)
        {
            for(j=1;j<=N;j++)
                {
                    L->edge[i][j]=0;
                }
        }
    int u,v;
    for(int k=0;k<M;k++)
        {
            scanf("%d %d",&u,&v);
            L->edge[u][v]=1;
            L->edge[v][u]=1;
        }
}
int BFS(juzhen* L,int start,int N)
{
    sequeue p;
    initsequeue(&p);
    Push(&p,start);
    int visit[MAX]={0};
    int dist[MAX]={0};
    visit[start]=1;
    int count=1;
    while(!isempty(&p))
        {
            int y=POP(&p);
            for(int i=1;i<=N;i++)
                {
                    if(L->edge[y][i]==1&&visit[i]==0)
                        {
                            visit[i]=1;
                            dist[i]=dist[y]+1;
                            Push(&p,i);
                            if(dist[i]<=6)
                            {
                                count++;
                            }
                        }
                }
        }
    return count;
}
int main()
{
    int N,M;
    scanf("%d %d",&N,&M);
    static juzhen L;
    creatadj(&L,N,M);
    for(int i=1;i<=N;i++)
        {
            int a=BFS(&L,i,N);
            double rate=100.0*a/N;
            printf("%d: %.2f%%\n",i,rate);
        }
    return 0;
}
