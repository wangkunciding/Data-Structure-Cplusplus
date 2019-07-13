#include<iostream>
#include<cstring>
#include <vector>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;
const int N = 6; //顶点数
bool visit[N];   //访问矩阵
int lowcost[N] = { 0 };//最小边
int map[N][N] = {   
	{INF,  7,  4,INF,INF,INF},
	{  7,INF,  6,  2,INF,  4},
	{  4,  6,INF,INF,  9,  8},
	{INF,  2,INF,INF,INF,  7},
	{INF,INF,  9,INF,INF,  1},
	{INF,  4,  8,  7,  1,INF}
};

 
/*边的定义*/
struct edge
{
       int u, v;                                //边的两个端点编号
       int cost;                                //边权
       edge(int x,int y, int c):u(x),v(y),cost(c){}
};
 
/*边的比较函数*/
bool cmp(edge a, edge b)
{
       return a.cost < b.cost;
}
 
/*并查集查询函数，返回x所在集合的根结点*/
int findFather(vector<int> father, int x)
{
       int a = x;
       while (x != father[x])
              x = father[x];
       while (a != father[a]) {
              int z = a;
              a = father[a];
              father[z] = x;
       }
       return x;
}
 
/*Kruskal算法求无向图的最小生成树*/
int Kruskal(int n, int m, vector<edge>& E)
{
       /*
       param
       n:                         图的顶点个数
       m:                         图中边的个数
       E:                         边的集合
       */
       vector<int> father(n);                                 //并查集数组
       int ans = 0;                                           //所求边权之和
       int NumEdge = 0;                                       //记录最小生成树边数
       for (int i = 0; i < n; i++)                            //初始化并查集
              father[i] = i;
       sort(E.begin(), E.end(), cmp);                         //所有边按边权从小到大排序
       for (int i = 0; i < m; ++i)                            //枚举所有边
       {
              int faU = findFather(father, E[i].u);           //查询端点u所在集合的根结点
              int faV = findFather(father, E[i].v);           //查询端点v所在集合的根结点
              if (faU != faV) {                               //如果不在一个集合中
                     father[faU] = faV;                       //合并集合（相当于把测试边加入到最小生成树）
                     ans += E[i].cost;
					 cout<<E[i].u<<"-》"<<E[i].v<<endl;
                     NumEdge++;                               //当前生成树边数加1
                     if (NumEdge == n - 1)                    //边数等于顶点数减1，算法结束
                           break;
              }
       }
       if (NumEdge != n - 1)                                  //无法连通时返回-1
              return -1;
       else
              return ans;                                     //返回最小生成树边权之和
}
 



int prim(int cur)
{
	int index = cur;
	int sum = 0;       //最短路径长 
	int i = 0 , j = 0;
	cout << index << "->";
	memset(visit,false, sizeof(visit));  //将某一块内存中的内容全部设置为指定的值， 这个函数通常为新申请的内存做初始化工作
	visit[cur] = true;
	for(i = 0; i < N; i++)
		lowcost[i] = map[cur][i];//初始化，将cur结点所有相连的边放入 

	for(i = 1; i < N; i++)//两重for循环 遍历每一个结点
	{
		int min= INF;   //定义一个变量min初始化为一个极大值 
		//第一个for循环  未访问的点与与索引点index的比较
		for(j = 0; j < N; j++)
		{
			if(!visit[j] && lowcost[j] < min)//找到未访问的点中，距离当前最小生成树距离最小的点
			{
				min = lowcost[j];  //不断更新与点cur的相连点的最短距离，将lowcost[j]权值更新数据到min上 更新权值 
				index = j;//将j数组下标更新到index中（即cur）更新结点 
			}
		}
		visit[index] = true;//标记距离最短的结点已经被访问过
		cout << index << "->";//输出新结点 
		sum += min;//权值累加 
		//第二个for循环  从index结点开始遍历的图中的新结点map[index][j]与最小生成树中lowcost[j]旧结点之间的权值遍历比较 更新lowcost
		for(j = 0; j < N; j++) 
		{
			if(!visit[j] && lowcost[j]>map[index][j])     
			{
				lowcost[j] = map[index][j];
			}
		}
	}
	cout << endl;
	return sum;               //返回最小生成树的总路径值
}
int main()
{
	cout<<"===============================prim==============================="<<endl;
	cout << prim(0) << endl;//从0开始
	cout << prim(1) << endl;//从1开始
	cout << prim(2) << endl;//从2开始
	cout << prim(3) << endl;//从3开始
	cout << prim(4) << endl;//从4开始
	cout << prim(5) << endl;//从5开始
	

	cout<<"===============================kurskal==============================="<<endl;
	edge medge[10] = {edge(0,1,4),edge(1,2,1),edge(2,3,6),edge(3,4,5),edge(0,4,1),edge(0,5,2),edge(1,5,3),edge(2,5,5),edge(3,5,4),edge(4,5,3)};
	vector<edge> E(medge, medge+10);
	int n = 6;
	int m = 10;
	int res = Kruskal(n, m, E);
	cout << res << endl;

	return 0;
}

