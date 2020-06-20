#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//Const
const long long Base=1e8; 
const int Maxn=1e2;
//Definition
char R[Maxn*8];
//Struct
struct _Big 
{
	long long big[Maxn];
	int sign,len;
	_Big(){Clean();}
	//Operation
	//signed
	inline void Clean()
	{
		memset(big,0,sizeof(big));
		sign=len=1;
	}
	inline void Read()//input this
	{
		scanf("%s",R+1);
		if(R[1]=='-'&&R[2]!='0')sign=-1;
		for(int i=strlen(R+1),w=1;i>=1;i--,w*=10)
		{
			if(w==Base)w=1,len++;
			if(R[i]!='-')big[len]+=w*(R[i]-48);
		}
	}
	inline void Write()//output this
	{
		if(sign==-1)putchar('-');
		printf("%lld",big[len]);
		for(int i=len-1,v=Base/10,w=v;i>=1;i--,w=v)
		{
			while(big[i]<w)putchar('0'),w/=10;
			printf("%lld",big[i]);
		}
	}
	inline _Big operator=(int n)
	{
		Clean();
		big[1]=n;
	}
	//unsign
	inline friend _Big Add(_Big x,_Big y)
	{
		_Big T;
		T.len=max(x.len,y.len);
		for(int i=1;i<=T.len;i++)
		{
			T.big[i]=x.big[i]+y.big[i];
			if(T.big[i]>=Base)
				T.big[i+1]+=T.big[i]/Base,
				T.big[i]%=Base;
		}
		if(T.big[T.len+1]>0)T.len++;
		return T;
	}
	inline friend _Big Sub(_Big x,_Big y)
	{
		_Big T;
		T.len=x.len;
		for(int i=1;i<=T.len;i++)
		{
			T.big[i]+=x.big[i]-y.big[i];
			if(T.big[i]<0)
				T.big[i+1]--,
				T.big[i]+=Base;
		}
		while(T.big[T.len]==0&&T.len>1)T.len--;
		return T;
	}
	inline friend _Big Mul(_Big x,_Big y)
	{
		_Big T;
		T.len=x.len+y.len-1;
		for(int i=1;i<=x.len;i++)
			for(int j=1;j<=y.len;j++)
			{
				T.big[i+j-1]+=x.big[i]*y.big[j];
				if(T.big[i+j-1]>=Base)
					T.big[i+j]+=T.big[i+j-1]/Base,
					T.big[i+j-1]%=Base;
			}
		if(T.big[T.len+1]>0)T.len++;
		return T;
	}
	inline friend _Big Div(_Big x,_Big y,_Big &m)
	{
		_Big T;
		T.len=x.len-y.len+1;
		for(int i=x.len,v=Base/10;i>=1;i--)
			for(int w=v;w>=1;w/=10)
			{
				for(int j=m.len;j>=1;j--)
					m.big[j+1]+=(m.big[j]*=10)/Base,
					m.big[j]=m.big[j]%Base;
					m.big[1]+=(x.big[i]/w)%10;
				if(m.big[m.len+1]>0)m.len++;
				while(Check(m,y)!=-1)m=Sub(m,y),T.big[i]+=w;
			}
		while(T.big[T.len]==0&&T.len>1)T.len--;
		return T;
	}
	inline friend int Check(_Big x,_Big y)
	{
		if(x.len>y.len) return 1;
		if(x.len<y.len) return -1;
		for(int i=x.len;i>=1;i--)
		{
			if(x.big[i]>y.big[i])return 1;
			if(x.big[i]<y.big[i])return -1;
		}
		return 0;
	}
	inline friend _Big Quick_Pow(_Big x,int y)
	{
		_Big T;T.big[1]=1;
		while(y!=0)
		{
			if(y%2==1)T=Mul(x,T);
			y/=2;x=Mul(x,x);
		}
		return T;
	}
	//Operator
	//sign
	inline friend int Check_Sign(_Big x,_Big y)
	{
		if(x.sign>y.sign)return 1;
		if(x.sign<y.sign)return -1;
		return 0;
	}
	inline friend _Big operator+(_Big x,_Big y)
	{
		_Big T;
		if(x.sign==y.sign)
			T=Add(x,y),
			T.sign=x.sign;
		else
			if(Check(x,y)==1)
				T=Sub(x,y),
				T.sign=x.sign;
			else if(Check(x,y)==-1)
				T=Sub(y,x),
				T.sign=y.sign;
		return T;
	}
	inline friend _Big operator-(_Big x,_Big y)
	{
		_Big T;
		if(x.sign!=y.sign)
			T=Add(x,y),
			T.sign=x.sign;
		else 
			if(Check(x,y)==1)
				T=Sub(x,y),
				T.sign=1;
			else if(Check(x,y)==-1)
				T=Sub(y,x);
				T.sign=-1;
		return T;
	}
	inline friend _Big operator*(_Big x,_Big y)
	{
		_Big T;
		T=Mul(x,y);
		T.sign=x.sign*y.sign;
		return T;
	}
	inline friend _Big operator/(_Big x,_Big y)
	{
		_Big T,m;
		T=Div(x,y,m);
		T.sign=x.sign*y.sign;
		return T;
	}
	inline friend _Big operator%(_Big x,_Big y)
	{
		_Big m;
		Div(x,y,m);
		m.sign=x.sign*y.sign;
		return m;
	}
	inline friend bool operator>(_Big x,_Big y)
	{
		int C=Check_Sign(x,y);
		if(C==0)C=Check(x,y);
		if(C==1)return true;
		else return false;
	}
	inline friend bool operator<(_Big x,_Big y)
	{
		int C=Check_Sign(x,y);
		if(C==0)C=Check(x,y);
		if(C==-1)return true;
		else return false;
	}
	inline friend bool operator>=(_Big x,_Big y)
	{
		int C=Check_Sign(x,y);
		if(C==0)C=Check(x,y);
		if(C!=-1)return true;
		else return false;
	}
	inline friend bool operator<=(_Big x,_Big y)
	{
		int C=Check_Sign(x,y);
		if(C==0)C=Check(x,y);
		if(C!=1)return true;
		else return false;
	}
	inline friend bool operator==(_Big x,_Big y)
	{
		int C=Check_Sign(x,y);
		if(C==0)C=Check(x,y);
		if(C==0)return true;
		else return false;
	}
}x,y,m;
int main()
{
	x.Read(),y.Read();
	(x*y).Write();
	return 0;
}
