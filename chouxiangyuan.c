#include<stdio.h>
typedef struct Circle
{
    double r;
    double x;
    double y;
}Circle;
void assign(Circle* p,double ri,double xi,double yi)
{
    (*p).r=ri;
    (*p).x=xi;
    (*p).y=yi;
}
void Area(Circle C)
{
    double s;
    s=3.14*C.r*3.14;
    printf("Area=%.2f\n",s);
}
int main()
{
    Circle C;
    assign(&C,2.0,1.0,1.0);
    Area(C);
    return 0;
}