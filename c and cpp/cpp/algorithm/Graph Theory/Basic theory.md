refer to [【图论】总汇（内含C++）](https://blog.csdn.net/weixin_66767924/article/details/133513083?fromshare=blogdetail&sharetype=blogdetail&sharerId=133513083&sharerefer=PC&sharesource=yourox&sharefrom=from_link)

# 一、图的各种定义
## 1.图的构成

- 图由点和边组成的。
- 有向图、有向边，是有方向的。
- **度**是一点所关联的边数。
- **出度有向图**中，从一个点出去的边数；**入度有向图**中，从一个点进来的边数。
- **自环**，邪恶的东西，能寄掉一些算法，需要特殊处理，一条边两端连着同一个点。
- **路径**，从一个点走到另一个点（可含环）；简单路径，就是不含环的路径。
- **环**，从一点出发在绕回这个点的路径
- 注：有向无环图（DAG），若设动态规划状态为点，转移为为边，这一定是DAG。   

## 2.树 

树，是一种无环、无向、连通的图，并且如果有x个点，那么就有x-1条边。

- 如果去掉连通那么就变成了森林。
- 如果去掉无向那么就变成了DAG了，而有一种特殊的DAG——有向树（2023.10.14对错误内容进行了更改，可放心食用😀），有向树分为内向树，和外向树，边指向根节点,是内向树，边非指向根节点，就是外向树。
- 如果去掉无环那就是一个普通的无向图，但是若只有一个环，那就是基环树（章鱼图）。但若每一条边都只在一个环里，那就是仙人掌图。
## 3. 二分图
就这样**两边只有点**，**中间只有边**（竟然还***有自环）！一但有**有奇数长度的环（奇环）**就不是二分图了**。
`二分图（Bipartite Graph）`是一种特殊的图，它的顶点集合可以划分为两个不相交的子集，使得每条边都连接这两个子集中的一个顶点和另一个顶点。换句话说，二分图中的所有边都只能在两个不同的子集

一个图  $G = (V, E)$  是二分图，当且仅当其顶点集 $V$ 可以分割为两个不相交的子集 $U$ 和 $W$ ，使得图中的每条边 $e$ 满足 $e$ 连接 $U$ 和 $W$ 中的一个顶点。图 $G$ 是二分图，当且仅当存在一个划分 $(U, W)$ 使得：
  $U \cup W = V$
  $U \cap W = \emptyset$
  $\forall (u, w) \in E, \text{其中 } u \in U \text{ 且 } w \in W$ 
由定义可知：包含自环的一定不是二分图；重边当作一条边来看即可。
### 1、特性

1. **没有奇环**：一个图是二分图当且仅当它不包含奇数长度的环。也就是说，所有环的长度都是偶数。
2. **两色定理**：二分图可以用两种颜色对顶点进行着色，使得每条边的两个端点的颜色不同。这种两种颜色的着色也称为`二部着色（Bipartite Coloring）`。
![[Pasted image 20250816191728.png]]

# 二、图的存储
## 1. 邻接矩阵
```cpp
int g[N][N];
```
随便建一个二维数组，![g_{i,j}](https://latex.csdn.net/eq?g_%7Bi%2Cj%7D)代表i点与j点之间有一条，边权为 ![g_{i,j}](https://latex.csdn.net/eq?g_%7Bi%2Cj%7D)，若没有边权有边则![g_{i,j}=1](https://latex.csdn.net/eq?g_%7Bi%2Cj%7D%3D1)。

- 内存消耗（空间复杂度）：![S(N^2)](https://latex.csdn.net/eq?S%28N%5E2%29)
- 查询效率（时间复杂度）：![O(1)](https://latex.csdn.net/eq?O%281%29)
## 2.邻接表
```cpp
vector<pair<int,int> >edge[N];//第一种
vector<int> edge[N];//第二种
```
 `edge[v][i].first`**和**`edge[v][i].second`分别表示与v点相连的**第i个点（第i条边）**和与v点相连的**第i条边的边权，**若没有边权，就要用第二种了（上方代码）**。
# 三、各类算法（大汇总😃）
## 1.判断二分图

**染色的方法~代码如下……**
```cpp
int col[maxn];
//col[i]==0 i点还没决定放哪边
//col[i]==1 i点放左边
//col[i]==2 i点放右边 
 
int main()
{
	cin >>n >> m;
	for (int i=1;i<=m;i++)
	{
		int s,e;
		cin >> s >> e;
		add_edge(s,e);
		add_edge(e,s);
	}
	bool able=true;//能够。
	for (int i=1;i<=n;i++)
		if (col[i] == 0)
		{
			col[i] = 1;
			queue<int> q;//还需要更新周围点放哪边的那些点 
			q.push(i); 
			while (q.size())
			{
				int now=q.front();
				q.pop();
				for (int i=0;i<g[now].size();i++)
				{
					int j=g[now][i];//是一条从now -> j的边
					if (col[j] == 0) //j点还没有放
					{
						col[j] = 3-col[now];
						q.push(j);
					}
					else if (col[now] == col[j]) able=false;
				}
			} 
		}
	if (able) cout << "yes\n";
	else cout << "no\n";
		
	return 0;
}
```

## 2.拓扑排序（用于DAG）

以下图片的拓扑排序是1、3、2、4、5，首先1、3入度为0**加入队列并删除**，2、4入度变为0加**入队列并删除**，5入度变为0加入队列并删除。

但是删除过于繁琐、费时，我们可以**假删。**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
vector<ll> edge[105];
bool vis[105];
ll n,in[105];
void add_edge(ll v,ll u){
	edge[v].push_back(u);
	in[u]++; 
}
queue<ll> Q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		ll v;
		while(1){
			cin>>v;
			if(v!=0)add_edge(i,v);
			else break;
		}	
	}
	for(int i=1;i<=n;i++){
		if(in[i]==0){
			cout<<i<<' ';
			Q.push(i);
		}//若入度为0直接加入，为后面bfs做基础。
	}
	while(Q.size()){
		int v=Q.front();
		Q.pop();
		for(int i=0;i<edge[v].size();i++){
			in[edge[v][i]]--;
			if(in[edge[v][i]]==0){
				cout<<edge[v][i]<<' ';
				Q.push(edge[v][i]);
			}
		}
	}//bfs，启动！
}
```
## 3.最短路
### **（1）定义**

从某点走到另一个点的最短路径就是最短路，现在我们有一个问题，怎么算**最短路的长度**？

- **单源最短路：**从一点出发，到所有点的最短路。
- **多源最短路：**从多点出发，到其他点的最短路。

我们设![dist_{i,j}](https://latex.csdn.net/eq?dist_%7Bi%2Cj%7D)为i到j的最短路长度。而现在我们要介绍一个等式三角等式，![dist_{i,j}+dist_{j,k} \geq dist_{i,k}](https://latex.csdn.net/eq?dist_%7Bi%2Cj%7D&plus;dist_%7Bj%2Ck%7D%20%5Cgeq%20dist_%7Bi%2Ck%7D) 。
### （2）弗洛伊德（floyd：浓浓的DP气味;多源最短路）

###### 前置定义……如下！

- **需要用邻接接矩阵。**
- ![f_{i,j,k}](https://latex.csdn.net/eq?f_%7Bi%2Cj%2Ck%7D)表示从 j 走到 k 经过的点的编号小于等于 i 的最短路。

```cpp
int main()
{
	cin >> n >> m;
	memset(f,0x3f,sizeof(f));
	for (int i=1;i<=n;i++)
		f[0][i][i] = 0;
	for (int i=1;i<=m;i++)
	{
		int s,e,d;
		cin >> s >> e >> d;
		f[0][s][e] = min(f[0][s][e],d);
	}
	
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++)
				f[i][j][k] = min(f[i-1][j][k], f[i-1][j][i] + f[i-1][i][k]);
				
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			cout << f[n][i][j] << "\n";
	
}
```

### 3）迪杰斯拉（dijkstra) 

###### 前置定义……如下！

**松弛操作：**通过一个点，将周围所有点最短路变短。

- ![dist_i](https://latex.csdn.net/eq?dist_i)到i点的最短路长度。
- ![done_i](https://latex.csdn.net/eq?done_i)代表i的的最短路是否求出来了 。
- g邻接表。

###### 普通代码……如下！

**时间复杂度：**![O(n^2+m)](https://latex.csdn.net/eq?O%28n%5E2&plus;m%29)

```cpp
void dijkstra(int s)//计算s到其他所有点的最短路 
{
	memset(dist,0x3f,sizeof(dist));
	dist[s] = 0;
	for (int i=1;i<=n;i++){
		//找还没有求出最短路的dist值最小的那个点 
		int p=0;
		for (int j=1;j<=n;j++)//O(n^2)
			if (!done[j] && (p==0 || dist[j] < dist[p])) p = j;
		done[p] = true;
		//更新其他点的最短路。 
		for (int j=0;j<g[p].size();j++)//O(m)
		{
			int q=g[p][j].first;
			int d=g[p][j].second;//这是一条从 p->q 长度为d的边。 
			if (dist[q] > dist[p] + d) dist[q] = dist[p] + d;
		} 
	}
}
```

这就是极限吗，代码……如下！
**时间复杂度（STL堆，以下代码）：![O((n+m)log(n+m))](https://latex.csdn.net/eq?O%28%28n&plus;m%29log%28n&plus;m%29%29)**
**时间复杂度（手写堆，非以下代码）：![O((n+m)log n)](https://latex.csdn.net/eq?O%28%28n&plus;m%29log%20n%29)**

```cpp
void dijkstra(int s)//计算s到其他所有点的最短路 。 
{
	memset(dist,0x3f,sizeof(dist));
	dist[s] = 0;
	priority_queue<pair<int,int> > heap;//first 最短路的相反数（转换小根堆，压入转相反数，压出转回去，你细品）， second 点的编号。 
	for (int i=1;i<=n;i++)
		heap.push(make_pair(-dist[i],i));
	for (int i=1;i<=n;i++)
	{
		while (done[heap.top().second])
			heap.pop();
		//找还没有求出最短路的dist值最小的那个点。 
		int p = heap.top().second;
		heap.pop();
		done[p] = true;
		//更新其他点的最短路。 
		for (int j=0;j<g[p].size();j++)
		{
			int q=g[p][j].first;
			int d=g[p][j].second;//这是一条从 p->q 长度为d的边 。 
			if (dist[q] > dist[p] + d){
				dist[q] = dist[p] + d;
				heap.push(make_pair(-dist[q],q));
			}//松弛。 
		} 
	}
}
```
### （4）贝尔曼·福德（ bellman-ford）

###### 前置定义……如下！

- **时间复杂度：**![O(nm)](https://latex.csdn.net/eq?O%28nm%29)
- **无数次松弛**的成果！
```cpp
cin>>n>>m;//n点m边。
for(int i=1;i<=m;i++)
	cin >>s[i]>>e[i]>>d[i];
memset(dist,0x3f,sizeof(dist));
dist[1]=0;//只能从1开始。
//dist[i]表示从1到i的最短路。
for (int i=1;i<n;i++)
	for (int j=1;j<=m;j++)
		dist[e[j]]=min(dist[e[j]],dist[s[j]]+d[j]);
//第i条边是从s[i]->e[i]长度为d[i]。 
```
### （5）SPFA（ bellman-ford的升级版）

###### 时间复杂度……如下！

- **最坏：![O(nm)](https://latex.csdn.net/eq?O%28nm%29)**
- **平均：![O(km)](https://latex.csdn.net/eq?O%28km%29)（![k \leq 20](https://latex.csdn.net/eq?k%20%5Cleq%2020)）。**
```cpp
int dist[maxn];//dist[i]到i点的最短路长度 
bool inq[maxn];//inq[i]代表i点是否在队列中 
void spfa(int s)//计算s到其他所有点的最短路 
{
	memset(dist,0x3f,sizeof(dist));
	dist[s]=0;
	queue<int> q;//用来存储可能改变其他点最短路的点 
	q.push(s);
	inq[s] = true;
	//最坏O(nm)
	//平均O(km) k<20 
	while (q.size() != 0)//队列不为空
	{
		int a = q.front();
		q.pop();
		inq[a] = false;
		for (int i=0;i<g[a].size();i++)
		{
			int b = g[a][i].first;
			int c = g[a][i].second;//一条从 a->b 长度为c的边
			if (dist[b] > dist[a] + c)
			{
				dist[b] = dist[a] + c;
				if (!inq[b])
				{
					inq[b] = true;
					q.push(b);
				}
			} 
		}
	} 
}
```

## 4.生成树 

### （1）定义

一张图只保留一些边，变成一颗树，这棵树就是生成树。最小生成树是生成树中边权之和最小的。只有在图连通的时候才有生成树。
### （2）克鲁斯卡尔（kruskal：求最小生成树的算法；贪心的气息）
前置定义……如下

我们将一个图每条边按权值排序，然后枚举排完序的序列，在空白图上进行加边，枚举时若加入某条边会形成环那就不加入了，否则加。

那怎么判段有环呢？我们可以用并查集，每加入一条边时，判断左右端点是否根节点一样，若一样，说明加边后会产生环，否则可以加。  

而这个加边不用，真正的加，我们求的是最小生成树，用一个sum记录边权和就可以了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int to[5005],n,m;
int go(int p){
	if (to[p] == p) return p;
	else return to[p]=go(to[p]);
}
struct edge{
	int s,e,d;
}ed[200005];
bool cmp(edge a,edge b){
	return a.d<b.d;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>ed[i].s>>ed[i].e>>ed[i].d;
	sort(ed+1,ed+m+1,cmp);
	for(int i=1;i<=n;i++)
		to[i]=i;
	int ans=0;
	for(int i=1;i<=m;i++){
		int p1=ed[i].s,p2=ed[i].e,d=ed[i].d;
		if (go(p1)!=go(p2)){
			ans+=d;
			to[go(p1)]=go(p2);
		}
	}
	for(int i=1;i<n;i++){
		if(go(i)!=go(i+1)){
			cout<<"orz";
			return 0;
		}
	}
	cout<<ans<<endl;
}
```

## 5.强联通分量

强联通分量，一个有向图的子图，其中任意两点都可以互相到达，要尽可能大。那怎么求强联通分量数量呢？强联通分量本质就是环，让我们在下文中解决这个问题。
### （1）前置定义

我们把它搞成一个**形似树的东西**！

![[tree_with_loop.png]]

**树边：** 不可言传，只可意会！ 
**回边（形成环）：** 从一个点指向自己祖先的边。 
**横叉边（扩大环）：** 既不是树边，也不是回边。
### （2）Tarjan求强联通分量
```cpp
#include<bits/stdc++.h>
using namespace std; 
#define ll long long
vector<ll> edge[100005]; 
ll n,m,s;
void add_edge(ll s,ll e){
	edge[s].push_back(e);
} 
int num;//当前dfs了几个点。
int dfn[10005];//dfn[i] 代表i点是第几个被dfs到的点。
int low[10005];
//low[i] 代表从i点出发 走 树边、回边、能扩大环的横叉边 能走到的所有点中dfn最小的是多少。
stack<int> sta;//用来存储 所有被 dfs 过 但还没有求出 强连通分量的点。
bool instack[10005];//instack[i] 代表i点是否在栈里面。
int cnt;//当前总共有多少个强连通分量。
int belong[10005];//belong[i]代表i点属于第几个强连通分量
void dfs(int i){
	num++,dfn[i]=low[i]=num;
	sta.push(i);
	instack[i]=1;
	for(int k=0;k<edge[i].size();k++){
		ll j=edge[i][k];
		if(!dfn[j]){//树边
			dfs(j);
			low[i]=min(low[i],low[j]); 
		}else{//回边横叉边
			if(instack[j])low[i]=min(low[i],dfn[j]);
		}
	}
	if(dfn[i]==low[i]){//i是它所属的强连通分量的最上面的点 
		cnt++;//新增了一个强连通分量
		while(sta.top()!=i){//栈顶不等于当前点
			belong[sta.top()]=cnt;//i和sta.top()一定属于同一个强连通分量
			instack[sta.top()]=0;
			sta.pop();
		}
		sta.pop();
		instack[i]=0;
		belong[i]=cnt;
	}
} 
vector<ll> Belong[10005];//Belong[i]是一个vector用来记录第i个强连通分量里面的所有点。
bool vis[10005];//vis[i]代表第i个强联通分量是否已经输出过了。 
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int p1,p2;
		cin>>p1>>p2;
		add_edge(p1,p2);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i])dfs(i);
		Belong[belong[i]].push_back(i);
	}
	cout<<cnt<<'\n'//有几个强连通分量 ;
	for(int i=1;i<=cnt;++i){
		sort(Belong[i].begin(),Belong[i].end());
	}
	for(int i=1;i<=n;++i){
		if(vis[belong[i]])continue;
		vis[belong[i]]=1;
		for(int j=0;j<Belong[belong[i]].size();++j){
			cout<<Belong[belong[i]][j]<<" ";
		}cout<<'\n';
	}
}
```