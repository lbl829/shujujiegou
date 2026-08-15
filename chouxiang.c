#include<stdio.h>
typedef struct Node
{
    int  data;
    struct Node* next;
}Node;
void assign(Node* p,int a,struct Node* nextNode)
{
    (*p).data=a;
    (*p).next=nextNode;
}
void printNode(struct Node* p)
{
    while(p!=NULL)
    {
        printf("%d ",(*p).data);
        p=(*p).next;
    }
}
int main()
{
    struct Node A,B,C,D;
    assign(&A,5,&B);
    assign(&B,10,&C);
    assign(&C,15,&D);
    assign(&D,20,NULL);
    printNode(&A);
    return 0;
}