#include<stdio.h>
#include<string.h>
char* print(char** a,int n)
{
	int mindex=0;
	if(n==0)
	{
		return "";
	}
	for(int i=1;i<n;i++)
	{
		if(strlen(a[i])<strlen(a[mindex]))
		{
			mindex=i;
		}
	}
	size_t samelen=strlen(a[mindex]);
	for(int i=0;i<n;i++)
	{
		size_t currlen=0;
		for(int j=0;j<samelen;j++)
		{
			if(a[i][j]!=a[mindex][j])
			{
				break;
			}
			currlen++;
		}
		if(samelen>currlen)
		{
			samelen=currlen;
		}
		else{
			samelen=samelen;
		}
	}
	a[mindex][samelen]='\0';
	return a[mindex];
}
int main()
{
	int n=3;
	char* ch[3]={"flower","floor","flow"};
	char* x=print(ch,3);
	printf("%s",x);
	return 0;
}