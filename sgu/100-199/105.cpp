#include <cstdio>
int n;
int main ()
{
	scanf("%d",&n);
	printf("%d\n",n/3*2+(n%3==0?0:n%3-1));
	return 0;
}
