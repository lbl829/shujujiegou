#include<stdio.h>
#include<string.h>
#define MAX 1000
typedef struct Queue
{
    int data[MAX];
    int front;
    int rear;
}Queue;
void init(Queue* L)
{
    L->front=0;
    L->rear=0;
}
void Push(Queue* L,int x)
{
    L->data[L->rear]=x;
    L->rear=(L->rear+1)%MAX;
}
int pop(Queue* L)
{
    int x;
    x=L->data[L->front];
    L->front=(L->front+1)%MAX;
    return x;
}
int size(Queue* L)
{
    return (L->rear-L->front+MAX)%MAX;
}
int main()
{
    int n;
    scanf("%d",&n);
    Queue A;
    init(&A);
    while(n--)
    {
        int y;
        scanf("%d",&y);
        if(y==1)
        {
            int c;
            scanf("%d",&c);
            Push(&A,c);
        }
        else if(y==2)
        {
            if(size(&A)==0)
                {
                    printf("Invalid\n");
                }
            else
            {
                int s=pop(&A);
                printf("%d\n",s);
            }
        }
        else if(y==3)
        {
            int t=size(&A);
            printf("%d\n",t);
        }
    }
    return 0;
}