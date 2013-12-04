#include <cstdio>
#include <cstdlib>
#include <cstring>

int n,a[310][310],g[310][310],i,j,k,l;
int s[310][310],u[310],point=0,flag;
int maxp;
int ans[300],f[310][310],x[310],y[310];

int dfs(int t,int p,int q)
{
	int i;

	u[t]=2*q+p;
	if(p==-1)x[q]++; 
	else y[q]++;
	for(i=1;i<=g[t][0];i++)
	{
		if(u[t]==u[g[t][i]])return 1;
		else
			if(! u[g[t][i]])
				if(dfs(g[t][i],-1-p,q))return 1;
	}
	return 0;
}

int main ()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		while(scanf("%d",&k) && k)
			a[i][k]=1;
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	if(i!=j)
	if(! (a[i][j] && a[j][i]))
	{
		g[i][++g[i][0]]=j;
		g[j][++g[j][0]]=i;
	}
	for(i=1;i<=n;i++)
		if(! u[i])
		{
			point++;
			flag=dfs(i,-1,point);
			if(flag)
			{
				printf("No solution\n");
				return 0;
			}
		}
	f[0][0]=1;
	for(i=0;i<point;i++)
	for(j=0;j<=n;j++)
		if(f[i][j])
		{
			f[i+1][j+x[i+1]]=1;
			f[i+1][j+y[i+1]]=1;
			s[i+1][j+x[i+1]]=0;
			s[i+1][j+y[i+1]]=1;
		}
	maxp=n;
	for(i=1;i<n;i++)
		if(f[point][i])
		if(maxp>abs(n-i-i))
		{
			j=i;
			maxp=abs(i-n+i);
		}
	for(i=point;i>=1;i--)
	{
		if(s[i][j]==0)
		{
			ans[2*i-1]=1;
			j-=x[i];
		}
		else
		{
			ans[2*i]=1;
			j-=y[i];
		}
	}
	j=0;
	for(i=1;i<=n;i++)
		if(ans[u[i]])j++;
	printf("%d",j);
	for(i=1;i<=n;i++)
		if(ans[u[i]])printf(" %d",i);
	printf("\n");
	printf("%d",n-j);
	for(i=1;i<=n;i++)
		if(! ans[u[i]])printf(" %d",i);
	printf("\n");	
	
	return 0;
}