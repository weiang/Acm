#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXN 30 + 5

int a[MAXN][15], f[MAXN], m[MAXN][MAXN], r[MAXN],w[MAXN];
int k, n, ok;
int flag;

int cmp1(const void *_p,const void *_q)
{
	int *p = (int *)_p;
	int *q = (int *)_q;
	return *p - *q;
}
int cmp2(const void *_p,const void *_q)
{
	int *p = (int *)_p;
	int *q = (int *)_q;
	return a[*p][1] - a[*q][1];
}

void com(int i, int j)
{
	for(int p = 1; p <= n; p ++)
		if(a[r[i]][p] >= a[r[j]][p]) return;
	ok = 1;    
}

void dp(int i)
{
	if(w[i] == -1) ;
	else dp(w[i]);
	if(w[i] == -1)
		printf("%d",r[i]);
	else printf(" %d",r[i]);    
}

void solve()
{
	memset(m,-1,sizeof(m));
	memset(f,0,sizeof(f));
	memset(w,-1,sizeof(w));
	for(int i = 0; i < MAXN; i ++)
		f[i] = 1;
	for(int i = 1; i <= k; i ++)
	{
		int q = 0;
		for(int j = i +1; j <= k; j ++)
		{
			ok = 0;
			com(i,j);//printf("i=%d j=%d ok=%d\n",i,j,ok);
			if(ok&&f[j]<f[i]+1) {f[j] = f[i] + 1;w[j] = i;}
			//    printf("f[i]=%d f[j] = %d w[j] = %d\n",f[i],f[j],w[j]);
		}
	}
	int max = -1;
	for(int i = 1; i <= k; i ++)
		if(f[i] > max) {max = f[i];flag = i;}
	printf("%d\n",max);
	//for(int i = 0; i <= k; i ++)
	//    printf("i = %d w[i] = %d\n",i,w[i]);
	dp(flag);
	printf("\n");
}

void input()
{
	memset(a,0,sizeof(a));
	while(scanf("%d%d",&k,&n) == 2)
	{
		for(int i = 1; i <= k; i ++)
			for(int j = 1; j <= n; j ++)
				scanf("%d",&a[i][j]);
		for(int i = 1; i <= k; i ++)
			qsort(a[i],n+1,sizeof(a[1][1]),cmp1);
		for(int i = 0; i <= k; i ++)
			r[i] = i;
		qsort(r,k+1,sizeof(r[0]),cmp2);
		solve();
	}
}

int main()
{
	input();
	return 0;
}
