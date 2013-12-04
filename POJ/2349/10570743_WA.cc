#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
#define maxn 510
#define maxm 510*510
int id[maxm],eu[maxm],ev[maxm],n,m,pnt[maxn],k;
double ew[maxm];
int cmp(const int &i,const int &j){return ew[i]<ew[j];}
int find(int x){if(x!=pnt[x])pnt[x]=find(pnt[x]);return pnt[x];}
int kruskal()
{
    int i,j=-1,p,x,y;
    double value;
    for(i=0;i<m;i++) 	id[i]=i;
    sort(id,id+m,cmp);
    for(i=0;i<n;i++)	pnt[i]=i;
    for(i=1;i<=k;i++)
    {
        while(1)
        {
	p=id[++j];            if(j>=m)return 0;            x=find(eu[p]);            y=find(ev[p]);
	if(x!=y)break;
        }
        value=ew[p];		pnt[y]=x;
    }
    printf("%.2f\n",value);
    return 1;
}
struct point
{
	double x,y;
}p[maxn];
double dist(point a,point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int main ()
{
	int t,i,j;
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d%d",&k,&n);
		m=0;
		for(i=0;i<n;i++)
		{
			scanf("%lf%lf",&p[i].x,&p[i].y);
			for(j=0;j<i;j++)
				eu[m]=i,ev[m]=j,ew[m++]=dist(p[i],p[j]);
		}
		kruskal();
	}
	
	return 0;
}