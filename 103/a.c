#include<cstdio>  
#include<cstring>  
#include<vector>  
#include<algorithm>   //vector<int> arr;  sort(arr.begin(),arr.end());  
using namespace std;  
#define MAXK 32  
vector<int> a[MAXK];      //push_back() 在Vector最后添加一个元素   
int k, n;   //维度  
int d[MAXK], vis[MAXK];  
int ans, maxi;  

int is(int cur, int j)  //判断连通，序号为参 i>j  
{  
	vector<int> &a1 = a[cur], &a2 = a[j];  
	int ok=1;  
	for(int i=0; i<n; i++)   //n维，n次  
		if(a1[i] <= a2[i]) { ok=0; break; }  //!等于也可以的  
	if(ok) return 1;  
	else return 0;  
}  

int dp(int cur) //第cur个框    1~k  
{  
	if(vis[cur]) return d[cur];  
	int max=1;  
	vis[cur] = 1;  
	for(int i=1; i<=k; i++)  if(i != cur && is(cur, i))  //注意不要跟自己判断 //慢的话可以把is的结果也记录下。  
	{  
		int t=dp(i)+1;  
		max = max>t? max: t;  
	}  
	ans = ans>max? ans: (maxi = cur, max);   //记录最大的d[i];  
	return d[cur] = max;  
}  

void print_path(int j)  
{  
	for(int i=1; i<=k; i++)  if(d[i] == d[j]-1 && is(j, i))  
	{ print_path(i); break; }   //!!  
	if(j!=maxi) printf("%d ", j);  
	else printf("%d", j);  
}  

int main()  
{  
	while(scanf("%d%d", &k, &n) != EOF)  
	{  
		ans=0;  
		memset(vis, 0, sizeof(vis));  
		for(int i=1; i<=k; i++)  
		{  
			for(int j=0; j<n; j++) { int t; scanf("%d", &t); a[i].push_back(t); }  
			//scanf("%d", &a[i][j]);    //不能这样用，还没vector分配空间，无法访问  
			sort(a[i].begin(), a[i].end()); //sort默认升序    
		}  
		for(int i=1; i<=k; i++) dp(i);       //  
		printf("%d\n", ans);  
		print_path(maxi);  
		printf("\n");  
		for(int i=1; i<=k; i++) a[i].clear();    //  
	}  
}  
