//code 
//include
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ls(x) node[x].l
#define rs(x) node[x].r
using namespace std;
const int Maxn=1e5+10;
const double A=1.0/3.0;
struct _Weight_Banlance_Leafy_Tree_Node
{
	int l,r,s,d;
	_Weight_Banlance_Leafy_Tree_Node()
	{
		Clear();
	}
	inline void Clear()
	{
		s=d=0;
		l=r=0;
	}
};
struct _Weight_Banlance_Leafy_Tree
{
	_Weight_Banlance_Leafy_Tree_Node node[2*Maxn];
	int len,trash[Maxn],trash_top;
	_Weight_Banlance_Leafy_Tree()
	{
		len=trash_top=0;
		memset(trash,0,sizeof(trash));
	}
	inline int Add(int l,int r)
	{
		int w=trash_top?trash[trash_top--]:++len;
		node[w].l=l;node[w].r=r;node[w].d=node[r].d;
		node[w].s=node[l].s+node[r].s;return w;
	}
	inline void Clean(int x){trash[++trash_top]=x;node[x].Clear();}
	inline void Copy(int f,int x){node[x]=node[f];}
	inline int New(int d)
	{
		int w=trash_top?trash[trash_top--]:++len;
		node[w].s=1;
		node[w].d=d;
		return w;
	}
	inline void Update(int x)
	{
		if(!node[ls(x)].s)return;
		node[x].d=node[rs(x)].d;
		node[x].s=node[ls(x)].s+node[rs(x)].s;
	}
	inline void Rotate(int x,bool w)
	{
		if(w)
		{
			int l=ls(x);
			node[x].r=Add(node[l].r,node[x].r);
			node[x].l=node[l].l;Clean(l);
		}
		else
		{
			int r=rs(x);
			node[x].l=Add(node[x].l,node[r].l);
			node[x].r=node[r].r;Clean(r);
		}
	}
	inline bool Check(int x)
	{
		return ((double)(min(node[ls(x)].s,node[rs(x)].s))>=(A*(double)(node[x].s)));
	}
	inline void Maintain(int x)
	{
		if(Check(x))return ;
		Rotate(x,node[ls(x)].s>node[rs(x)].s);
	}
	inline void Insert(int now,int x)
	{
		if(node[now].s==1)
		{
			node[now].l=New(min(node[now].d,x));
			node[now].r=New(max(node[now].d,x));
			Update(now);return;
		}
		Maintain(now);
		if(x<=node[ls(now)].d)Insert(ls(now),    x);else Insert(rs(now),    x);
		Update(now);
	}
	inline void Delete(int now,int fa,int x)
	{
		if(node[now].s==1)
		{
			int w=(ls(fa)==now)?rs(fa):ls(fa);
			Copy(w,fa);Clean(now);Clean(w);
			return;
		}
		Maintain(now);
		if(x<=node[ls(now)].d)Delete(ls(now),now,x);else Delete(rs(now),now,x);
		Update(now);
	}
	inline int Rank(int now,int x)
	{
		if(node[now].s==1)return 1;
		Maintain(now);
		if(x<=node[ls(now)].d)return Rank(ls(now),x);
		else return  node[ls(now)].s+Rank(rs(now),x);
	}
	inline int Select(int now,int k)
	{
		if(node[now].s==k)return node[now].d;
		Maintain(now);
		if(k<=node[ls(now)].s)return Select(ls(now),k);
		else return  Select(rs(now),k-node[ls(now)].s);
	}
	inline int Prev(int now,int x)
	{
		return Select(now,Rank(now,x)-1);
	}
	inline int Next(int now,int x)
	{
		return Select(now,Rank(now,x+1));
	}
}T;
int main()
{
	int n,rt=T.New(2147483647);scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int cz,x;scanf("%d%d",&cz,&x);
             if(cz==1) T.Insert(rt,x);
        else if(cz==2) T.Delete(rt,0,x);
        else if(cz==3) printf("%d\n",T.Rank(rt,x));
        else if(cz==4) printf("%d\n",T.Select(rt,x));
        else if(cz==5) printf("%d\n",T.Prev(rt,x));
        else if(cz==6) printf("%d\n",T.Next(rt,x));
	}
}
