#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
    int data;
    struct Node* next;
}Node,*LinkList;
void creatlist(LinkList* L)
{
    int n;
    *L=NULL;
    Node* r=NULL;
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        Node* p;
        p=(Node*)malloc(sizeof(Node));
        p->data=a[i];
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
}
void charu(LinkList* L)
{
    int x;
    scanf("%d",&x);
    Node* p=*L;
    Node* pre;
    pre=NULL;
    Node* q;
    q=(Node*)malloc(sizeof(Node));
    q->data=x;
    q->next=NULL;
    while(p!=NULL&&p->data<x)
    {
        pre=p;
        p=p->next;
    }
    if(pre==NULL)
    {
        q->next=p;
        *L=q;
    }
    else
    {
        q->next=p;
        pre->next=q;
    }
}
void printlist(LinkList L)
{
    Node* p=L;
    if(p==NULL)
    {
        return;
    }
    printf("%d",p->data);
    p=p->next;
    while(p!=NULL)
    {
        printf(" %d",p->data);
        p=p->next;
    }
}
int main()
{
    LinkList A;
    creatlist(&A);
    charu(&A);
    printlist(A);
    return 0;
}