#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
    int data;
    struct Node* next;
}Node,*LinkList;
void creatlist(LinkList* L)
{
    int N;
    *L=NULL;
    Node* r=NULL;
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        Node* p=(Node*)malloc(sizeof(Node));
        p->data=i;
        p->next=NULL;
        if(*L==NULL)
        {
            *L=p;
            r=p;
        }
        else
        {
            r->next=p;
            r=p;
        }
    }
    r->next=*L;
}
void POP(LinkList* L)
{
    if(*L==NULL)
    {
        return;
    }
    int p;
    scanf("%d",&p);
    Node* pre=NULL;
    Node* q=*L;
    int  flag=1;
    while(pre!=q)
    {
       for(int i=1;i<p;i++)
       {
        pre=q;
        q=q->next;
       }
       if(flag==0)
       {
        printf(" ");
       }
       printf("%d",q->data);
       flag=0;
       pre->next=q->next;
       q=pre->next;
    }
    if(flag==0)
    {
        printf(" ");
    }
    printf("%d",q->data);
}
int main()
{
    LinkList L;
    creatlist(&L);
    POP(&L);
    return 0;
}