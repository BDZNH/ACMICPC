#include <cstdio>
#include <string.h>
#include <iostream>
using namespace std;

int a[1100][200],b[200],c[200];
char s1[200],s2[200];

int bj(int *x,int *y)
{
	if(x[0]>y[0])return 1;
	if(x[0]<y[0])return -1;
	for(int i=x[0];i>=1;i--)
	{
		if(x[i]>y[i])return 1;
		if(x[i]<y[i])return -1;
	}
	return 0;
}

int search(int *d,int s,int t)
{
	int mid,q;

	while (s<t)
	{
		mid=(s+t)/2+(s+t)%2;
		q=bj(a[mid],d);
		if(q==0)return mid;
		if(q<0)s=mid;
		else t=mid-1;
	}
	return s;
}

int main ()
{
	a[0][0]=a[1][1]=a[1][0]=a[2][0]=1;
	a[2][1]=2;
	for(int i=3;i<=1000;i++)
	{
		int k=a[i-1][0]>a[i-2][0]?a[i-1][0]:a[i-2][0];
		for(int j=1;j<=k;j++)
		{
			a[i][j]+=a[i-1][j]+a[i-2][j];
			a[i][j+1]=a[i][j]/10;
			a[i][j]%=10;
		}
		if(a[i][k+1]>0)k++;
		a[i][0]=k;
	}
	while (scanf("%s %s",s1,s2))
	{
		if(strcmp(s1,"0")==0 && strcmp(s2,"0")==0)break;
		b[0]=strlen(s1); c[0]=strlen(s2);
		if(strcmp(s1,"0")==0)s1[0]='1';
		for(int i=0;s1[i];i++) b[b[0]-i]=s1[i]-'0';
		for(int i=0;s2[i];i++) c[c[0]-i]=s2[i]-'0';

		int i=search(b,1,1000),j=search(c,1,1000),q1,q2;
		q1=bj(b,a[i]); q2=bj(c,a[j]);
		q1=bj(b,a[i]); q2=bj(c,a[j]);
		if(q1==0 && q2==0)printf("%d\n",j-i+1);
		else if(q1!=0 && q2!=0)	printf("%d\n",j-i);
			else if(q1==0)printf("%d\n",j-i+1);
				else printf("%d\n",j-i);
	}
	
	return 0;
}