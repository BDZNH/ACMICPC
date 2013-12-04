#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
#define INF 10000000000000000LL
#define N 1000010
struct Node;
typedef pair<Node*,Node*> Pair;
Node *null,*root;
struct Node
{
    long long sz,val,lzy1,lzy2,mn;
    Node *lft,*rht;
    Pair split(long long);
    void add(long long v)
    {
    	if(this==null) return;
        lzy1+=v;
        val+=v;
        mn+=v;
    }
    Node *pushup()
    {
        sz=lft->sz+1+rht->sz;
        mn=min(min(lft->mn,rht->mn),val);
        return this;
    }
    Node *pushdown()
    {
    	if(this==null) return this;
        if(lzy1)
        {
            lft->add(lzy1);
            rht->add(lzy1);
            lzy1=0;
        }
        if(lzy2)
        {
        	if(lft!=null) lft->lzy2^=1;
        	if(rht!=null) rht->lzy2^=1;
        	swap(lft,rht);
        	lzy2=0;
        }
        return this;
    }
};
bool random(long long a,long long b)
{
    return double(rand())/RAND_MAX<(double)a/(a+b);
}
Node *merge(Node *p,Node *q)
{
    if(p==null) return q;
    if(q==null) return p;
    if(random(p->sz,q->sz))
    {
        p->pushdown();
        p->rht=merge(p->rht,q);
        return p->pushup();
    }
    q->pushdown();
    q->lft=merge(p,q->lft);
    return q->pushup();
}
Pair Node::split(long long need)
{
    if(this==null) return make_pair(null,null);
    pushdown();
    if(lft->sz>=need)
    {
        Pair ret=lft->split(need);
        lft=null;
        pushup();
        return make_pair(ret.first,merge(ret.second,this));
    }
    Pair ret=rht->split(need-(lft->sz+1));
    rht=null;
    pushup();
    return make_pair(merge(this,ret.first),ret.second);
}
Node data[N*2];
long long cnt;
Node* newnode(long long c)
{
    Node *x;
    x=&data[cnt++];
    x->lft=x->rht=null;
    x->sz=1; x->lzy1=x->lzy2=0;
    x->val=x->mn=c;
    return x;
}
void init()
{
    cnt=1;
    null=&data[0];
    null->sz=0;
    null->val=null->mn=INF;
    null->lzy1=null->lzy2=0;
    null->lft=null->rht=null;
}
//---------------------------------------------------------
void print(Node *rt)
{
	if(rt==null) return;
	print(rt->lft);
	printf("%lld ",rt->val);
	print(rt->rht);
}
long long n,m;
char ord[20];
long long a,b,c;
int main ()
{
    init();
    root=null;
    scanf("%lld",&n);
    for(long long i=0;i<n;i++)
    {
        long long a;
        scanf("%lld",&a);
        root=merge(root,newnode(a));
    }
    scanf("%lld",&m);
    while (m--)
    {
        scanf("%s",ord);
        if(ord[0]=='A')
        {
            scanf("%lld%lld%lld",&a,&b,&c);
            Pair ret1=root->split(a-1);
            Pair ret2=ret1.second->split(b-a+1);
            ret2.first->add(c);
            root=merge(ret1.first,merge(ret2.first,ret2.second));
        }else if(ord[0]=='M')
        {
            scanf("%lld%lld",&a,&b);
            Pair ret1=root->split(a-1);
            Pair ret2=ret1.second->split(b-a+1);
            printf("%lld\n",ret2.first->mn);
            root=merge(ret1.first,merge(ret2.first,ret2.second));
        }else if(ord[0]=='D')
        {
            scanf("%lld",&a);
            Pair ret1=root->split(a-1);
            Pair ret2=ret1.second->split(1);
            root=merge(ret1.first,ret2.second);
        }else if(ord[0]=='I')
        {
            scanf("%lld%lld",&a,&b);
            Pair ret1=root->split(a);
            Node *r=merge(ret1.first,newnode(b));
            root=merge(r,ret1.second);
        }else if(ord[3]=='O')
        {
            scanf("%lld%lld%lld",&a,&b,&c);
            Pair ret1=root->split(a-1);
            Pair ret2=ret1.second->split(b-a+1);
            Pair ret3=ret2.first->split(b-a+1-c);
            root=merge(ret1.first,merge(merge(ret3.second,ret3.first),ret2.second));
        }
        else
        {
        	scanf("%lld%lld",&a,&b);
        	Pair ret1=root->split(a-1);
            Pair ret2=ret1.second->split(b-a+1);
            ret2.first->lzy2=1;
            root=merge(ret1.first,merge(ret2.first,ret2.second));
        }
    }
    return 0;
}