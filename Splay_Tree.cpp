#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//Const
const int Maxn=110000;
//Definition
//Struct
struct _Splay_Tree_Node
{
	int d,n,s,f,son[2];
	//the date of the node
	//the number of the same date
	//the size of the tree
	//the father node of this node
	//the son node of this node
};
struct _Splay_Tree
{
	//Define
	#define ls(x) node[x].son[0]
	#define rs(x) node[x].son[1]
	//Definition
	_Splay_Tree_Node node[Maxn];
	int len,root;
	_Splay_Tree()
	{
		len=root=0;
	}
	//Operation
	inline void Update(int now)//Update the size
	{
		node[now].s=node[ls(now)].s+node[rs(now)].s+node[now].n;
	}
	inline void Add(int d,int f)//Add a node
	{
		len++;
		node[len].d=d;node[len].n=1;
		node[len].s=1;node[len].f=f;
		if(d<node[f].d) ls(f)=len;
		else			rs(f)=len;
		ls(len)=rs(len)=0;
	}
	inline void Rotate(int x,bool w)
	{
		int f=node[x].f,g=node[f].f;
		bool v=(rs(g)==f);int r , R;//son father
		
		r=node[x].son[w];
		R=f;
		node[R].son[not(w)]=r;
		if(r!=0)node[r].f=R;
		
		r=x;
		R=g;
		node[R].son[v]=r;
		node[r].f=R;		
		r=f;
		R=x;
		node[R].son[w]=r;
		node[r].f=R;
		Update(f);
		Update(x);
	}
	inline void Splay(int x,int rt)
	{
		while(node[x].f!=rt)
		{
			int f=node[x].f,g=node[f].f;
			if(g==rt)
			{
					 if(ls(f)==x)Rotate(x, true);
				else if(rs(f)==x)Rotate(x,false);
			}
			else
			{
					 if(ls(f)==x&&ls(g)==f)Rotate(f, true),Rotate(x, true);
				else if(rs(f)==x&&rs(g)==f)Rotate(f,false),Rotate(x,false);
				else if(ls(f)==x&&rs(g)==f)Rotate(x, true),Rotate(x,false);
				else if(rs(f)==x&&ls(g)==f)Rotate(x,false),Rotate(x, true);
			}
		}
		if(rt==0)root=x;
		return ;
	}
	inline int Find(int d)
	{
		int x=root;
		while(node[x].d!=d)
		{
			if(d<node[x].d)
			{
				if(!ls(x))break;
				else x=ls(x);
			}
			else
			{
				if(!rs(x))break;
				else x=rs(x);
			}
		}
		return x;
	}
	inline void Insert(int d)
	{
		if(root==0){Add(d,0);root=len;return ;}
		int x=Find(d);
		if(node[x].d==d)
		{
			node[x].n++;
			Update(x);
			Splay( x ,0);
		}
		else
		{
			Add(d,x);
			Update(x);
			Splay(len,0);
		}
	}
	inline void Delete(int d)
	{
		int x=Find(d);if(node[x].d!=d)return ;
		Splay(x,0);
			 if(node[x].n>1){node[x].n--;Update(x);return;}
		else if(ls(x)==0&&rs(x)==0){root=0;len=0;}
		else if(ls(x)==0&&rs(x)!=0){root=rs(x);node[root].f=0;}
		else if(ls(x)!=0&&rs(x)==0){root=ls(x);node[root].f=0;}
		else
		{
			int p=ls(x);
			while(rs(p))p=rs(p);
			Splay(p,x) ;
			int r=rs(x),R=p;
			node[R].son[1]=r;
			node[r].f=R;
			root=R;
			node[root].f=0;
			Update(R);
		}
	}
	inline int Rank(int d)
	{
		int x=Find(d);Splay(x,0);
		return node[ls(x)].s+1;
	}
	inline int Select(int k)
	{
		int x=root;
		while(true)
		{
			if(k<=node[ls(x)].s)x=ls(x);
			else if(k>node[ls(x)].s+node[x].n){k-=node[ls(x)].s+node[x].n;x=rs(x);}
			else break;
		}
		Splay(x,0);
		return node[x].d;
	}
	inline int Prev(int d)
	{
		int x=Find(d);Splay(x,0);
		if(d<=node[x].d&&ls(x)!=0)
		{
			x=ls(x);
			while(rs(x))x=rs(x);
		}
		if(node[x].d>=d)x=0;
		return x;
	}
	inline int Next(int d)
	{
		int x=Find(d);Splay(x,0);
		if(d>=node[x].d&&rs(x)!=0)
		{
			x=rs(x);
			while(ls(x))x=ls(x);
		}
		if(node[x].d<=d)x=0;
		return x;
	}
}T;
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
    {
        int cz,x;scanf("%d%d",&cz,&x);
             if(cz==1) T.Insert(x);
        else if(cz==2) T.Delete(x);
        else if(cz==3) printf("%d\n",T.Rank(x));
        else if(cz==4) printf("%d\n",T.Select(x));
        else if(cz==5) printf("%d\n",T.node[T.Prev(x)].d);
        else if(cz==6) printf("%d\n",T.node[T.Next(x)].d);
    }
	return 0;
}

