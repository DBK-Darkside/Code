//code 
//include
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ls(x) node[x].l
#define rs(x) node[x].r
using namespace std;
const int Maxn=500000+10;
const double A=1.0/3.0;
struct _Persistent_Weight_Banlance_Leafy_Tree_Node
{
	int l,r,s,d;
	_Persistent_Weight_Banlance_Leafy_Tree_Node()
	{
		Clear();
	}
	inline void Clear()
	{
		s=d=0;
		l=r=0;
	}
};
struct _Persistent_Weight_Banlance_Leafy_Tree
{
	_Persistent_Weight_Banlance_Leafy_Tree_Node node[25*Maxn];
	int len,trash[25*Maxn],trash_top;
	_Persistent_Weight_Banlance_Leafy_Tree()
	{
		len=trash_top=0;
		memset(trash,0,sizeof(trash));
	}
	inline int Add(int l,int r)
	{
		int w=trash_top?trash[trash_top--]:++len;
		node[w].l=l;node[w].r=r;node[w].d=node[r].d;
		node[w].s=node[l].s+node[r].s;
		return w;
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
	inline int Insert(int now,int x)
	{
		if(node[now].s==1)
		{
			int Now=New(node[now].d);
			node[Now].l=New(min(node[Now].d,x));
			node[Now].r=New(max(node[Now].d,x));
			Update(Now);return Now;
		}
		Maintain(now);
		if(x<=node[ls(now)].d)
			return Add(Insert(ls(now),x),rs(now));
		else 
			return Add(ls(now),Insert(rs(now),x));
	}
	inline int Delete(int now,int fa,int x)
	{
		if(node[now].s==1)
			return (node[now].d!=x)?now:-1;
		Maintain(now);
		int l=ls(now),r=rs(now);
		if(x<=node[l].d)
		{
			int d=Delete(l,now,x);
			return d==-1?r:Add(d,r);
		}
		else
		{
			int d=Delete(r,now,x);
			return d==-1?l:Add(l,d);
		}
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
		int P=Select(now,Rank(now,x)-1);
		return P<x?P:-2147483647;
	}
	inline int Next(int now,int x)
	{
		int N=Select(now,Rank(now,x+1));
		return N>x?N: 2147483647;
	}
}T;
int root[Maxn],n;
int main()
{
	scanf("%d",&n);
	root[0]=T.New(2147483647);
	for(int i=1;i<=n;i++)
	{
		int cz,la,x;scanf("%d%d%d",&la,&cz,&x);
		root[i]=root[la];
             if(cz==1)root[i]=T.Insert(root[la],x);
        else if(cz==2)root[i]=T.Delete(root[la],0,x);
        else if(cz==3) printf("%d\n",T.Rank(root[i],x));
        else if(cz==4) printf("%d\n",T.Select(root[i],x));
        else if(cz==5) printf("%d\n",T.Prev(root[i],x));
        else if(cz==6) printf("%d\n",T.Next(root[i],x));
	}
}
