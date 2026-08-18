#include<stdio.h>
int getValue(char c)
{
    switch(c)
    {
        case 'I':return 1;
        case 'V':return 5;
        case 'X':return 10;
        case 'L':return 50;
        case 'C':return 100;
        case 'D':return 500;
        case 'M':return 1000;
        dafault:return 0;
    }
}
int romanToInt(char* S)
{
    int sum=0;
    for(int i=0;S[i]!='\0';i++)
    {
        int curr=getValue(S[i]);
        int next=getValue(S[i+1]);
        if(curr<next)
        {
            sum-=curr;
        }
        else
        {
            sum+=curr;
        }
    }
    return sum;
}
int main()
{
    char S[100];
    scanf("%s",S);
    int result=romanToInt(S);
    printf("%d\n",result);
    return 0;
}