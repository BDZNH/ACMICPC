#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<ctime>
#include<vector>
#include<utility>
using namespace std;
#define INF (1<<30)
#define EPS 1e-6
#define PI acos(-1)
#define lowbit(x) ((x) & (-(x)))
#define IDX(l,r) ((l)+(r) | (l)!=(r))
#define ABS(x) ((x)>0?(x):-(x))
#define SET(a,b) memset(a,b,sizeof(a))
#define NN 40
#define MM 10010
int rands()
{
	static int x=1364684679;
	x+=(x<<2)+1;
	return x;
}
struct point
{
	double x,y;
	int init(){return scanf("%lf%lf",&x,&y);}
	point operator + (point a)
	{ point ret; ret.x=x+a.x; ret.y=y+a.y; return ret; }
	point operator - (point a)
	{ point ret; ret.x=x-a.x; ret.y=y-a.y; return ret; }
	double operator * (point a) { return x*a.y-y*a.x; }
	double operator ^ (point a) { return x*a.x+y*a.y; }
};
struct circle{ point o; double r; };
struct point3
{
	double x,y,z;
	int init(){return scanf("%lf%lf%lf",&x,&y,&z);}
	point3 operator + (point3 a)
	{ point3 ret; ret.x=x+a.x; ret.y=y+a.y; ret.z=z+a.z; return ret; }
	point3 operator - (point3 a)
	{ point3 ret; ret.x=x-a.x; ret.y=y-a.y; ret.z=z-a.z; return ret; }
	point3 operator * (point3 a)
	{
		point3 ret;
		ret.x=y*a.z-z*a.y; ret.y=z*a.x-x*a.z; ret.z=x*a.y-y*a.x;
		return ret;
	}
	double operator ^ (point3 a){ return x*a.x+y*a.y+z*a.z;  }
};
double xmult(point p0,point p1,point p2)
{ return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x); }
point3 xmult3(point3 p0,point3 p1,point3 p2)
{
	point3 ret;
	ret.x=(p1.y-p0.y)*(p2.z-p0.z)-(p1.z-p0.z)*(p2.y-p0.y);
	ret.y=(p1.z-p0.z)*(p2.x-p0.x)-(p1.x-p0.x)*(p2.z-p0.z);
	ret.z=(p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
	return ret;
}
double dot(point a,point b){ return a.x*b.x+a.y*b.y; }
double dot3(point3 a,point3 b){ return a.x*b.x+a.y*b.y+a.z*b.z; }
double dist(point a,point b)
{ return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
double dist3(point3 a,point3 b)
{ return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z)); }
struct matrix
{
	int n; int a[NN][NN];
	void clear(){ memset(a,0,sizeof(a)); }
	void init(){ clear(); for(int i=1;i<=n;i++) a[i][i]=1; }
	matrix operator * (matrix b)
	{
		matrix c; c.n=n;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			c.a[i][j]=0;
			for(int k=1;k<=n;k++) c.a[i][j]+=a[i][k]*b.a[k][j];
		}
		return c;
	}
	matrix operator + (matrix b)
	{
		matrix c; c.n=n;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			c.a[i][j]=a[i][j]+b.a[i][j];
		return c;
	}
	void printmatrix()
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				printf("%d ",a[i][j]);
			printf("\n");
		}
	}
};
struct bignumber
{
	int n;
	int a[MM];
	void clear()
	{ n=0; memset(a,0,sizeof(a)); }
	void init(char *s)
	{
		clear(); n=strlen(s);
		for(int i=0;s[i];i++) a[n-i]=s[i]-'0';
		while (a[n]==0 && n>1) n--;
	}
	void init(int s)
	{
		clear();
		if(s==0) { n=1; a[1]=0; return; }
		while (s) { a[++n]=s%10; s/=10; }
	}
	void output()
	{ for(int i=n;i>0;i--) printf("%d",a[i]); printf("\n"); }
	int operator < (bignumber b)
	{
		if(n<b.n) return 1; if(n>b.n) return 0;
		for(int i=n;i>0;i--)
		{
			if(a[i]<b.a[i]) return 1;
			if(a[i]>b.a[i]) return 0;
		}
		return 0;
	}
	int operator == (bignumber b)
	{
		if(n!=b.n) return 0;
		for(int i=n;i>0;i--)
			if(a[i]!=b.a[i]) return 0;
		return 1;
	}
};
bignumber operator + (bignumber a,bignumber b)
{
	a.n=max(a.n,b.n);
	for(int i=1;i<=a.n;i++)
	{
		a.a[i]+=b.a[i];
		a.a[i+1]+=a.a[i]/10;
		a.a[i]%=10;
	}
	if(a.a[a.n+1]>0) a.n++;
	return a;
}
bignumber operator - (bignumber a,bignumber b)
{
	for(int i=1;i<=a.n;i++)
	{
		a.a[i]-=b.a[i];
		if(a.a[i]<0) { a.a[i+1]--; a.a[i]+=10; }
	}
	while (a.a[a.n]==0 && a.n>1) a.n--;
	return a;
}
bignumber operator * (bignumber a,int b)
{
	for(int i=1;i<=a.n;i++)
	{ a.a[i]=a.a[i]*b+a.a[i-1]/10; a.a[i-1]%=10; }
	while (a.a[a.n]>=10)
	{ a.n++; a.a[a.n]=a.a[a.n-1]/10; a.a[a.n-1]%=10; }
	return a;
}
bignumber operator / (bignumber a,int b)
{
	int tmp=0;
	for(int i=a.n;i>0;i--)
	{ tmp=tmp*10+a.a[i]; a.a[i]=tmp/b; tmp%=b; }
	while (a.a[a.n]==0 && a.n>1) a.n--;
	return a;
}
bignumber gcd(bignumber a,bignumber b)
{
	int ans=0;
	bignumber c;
	while (1)
	{
		if(a.n==1 && a.a[1]==0) { c=b; break; }
		if(b.n==1 && b.a[1]==0) { c=a; break; }
		int flag=0;
		if(a.a[1]%2==0) a=a/2,flag++;
		if(b.a[1]%2==0) b=b/2,flag++;
		if(flag==2) ans++;
		if(! flag)
		if(a<b) b=b-a;
		else a=a-b;
	}
	while (ans--) c=c*2;
	return c;
}
int fastget()
{
	char c; int ans=0; c=getchar();
	int sign=1;
	while (! (c>='0' && c<='9' || c=='-')) c=getchar();
	if(c=='-') sign=-1,c=getchar();
	while (c>='0' && c<='9')
	{
		ans=(ans<<3)+(ans<<1)+c-'0';
		c=getchar();
	}
	return ans*sign;
}
void fastput(int x)
{
	char s[12]; int a=0;
	if(x==0) puts("0");
	else
	{
		if(x<0) putchar('-'),x=-x;
		while (x) { s[a++]=x%10+'0'; x/=10; }
		for(a--;a>=0;a--) putchar(s[a]);
		putchar('\n');
	}
}
int n,m;
long long dp[2][1<<12][110];
int c[1<<12];
int main()
{
	dp[0][0][0]=1;
	cin>>n>>m;
	for(int i=1;i<=(1<<n);++i)
		c[i]=c[i>>1]+(i&1);
	for(int i=1;i<=n;++i)
	{
		memset(dp[i&1],0,sizeof(dp[i&1]));
		for(int j=0;j<(1<<n);++j)
		if( !(j&(j<<1)) && !(j&(j>>1)) )
		for(int k=0;k<=m;++k)
			if(c[j]<=k)
			for(int l=0;l<(1<<n);++l)
				if( !(l&(l<<1)) && !(l&(l>>1)) )
				if( !(j&l) && !((j<<1)&l) && !((j>>1)&l) )
					dp[i&1][j][k]+=dp[(i&1)^1][l][k-c[j]];
		/*
		printf("i = %d\n",i);
		for(int j=0;j<(1<<n);++j)
		{
			for(int k=0;k<=m;++k)
				printf("%d ",dp[i&1][j][k]);
			printf("\n");
		}
		*/
	}
	long long ans=0;
	for(int j=0;j<(1<<n);++j) ans+=dp[n&1][j][m];
	cout<<ans<<endl;
	return 0;
}
