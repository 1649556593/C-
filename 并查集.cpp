#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
/*
并查集：根据已有关系来判断各个节点是否在同一集合
判断规则：根据关系构建树(但是通过集合进行简化)，如果两个节点的根节点是一样的那么就是在同一集合
并查集构建规则：
前者为父亲后者为儿子
如果一个节点遇到有多个父亲，把节点所在的树的根节点进行合并即可
*/
#if 0
bool find(vector<int>& Disjoint_Set_Union, int i, int j)
{
	while (Disjoint_Set_Union[j] != j)
	{
		j = Disjoint_Set_Union[j];
	}
	while (Disjoint_Set_Union[i] != i)
	{
		i = Disjoint_Set_Union[i];
	}
	if (i == j)
		return true;
	else
		return false;
}
//并查集find优化
//大多数情况下，在查询过程中只关心根节点是什么，并不关系这棵树的形态，
//因此在查询操作的时候将访问过的每个点的父节点修改成树根，这样的方法叫做路径压缩。
bool find2(vector<int>& Disjoint_Set_Union, int i, int j)
{
	int temp1 = j;
	vector<int>vec1;
	int temp2 = i;
	vector<int>vec2;
	while (Disjoint_Set_Union[j] != j)
	{
		vec1.push_back(j);
		j = Disjoint_Set_Union[j];
	}
	for (auto it : vec1)
	{
		Disjoint_Set_Union[it] = j;
	}
	while (Disjoint_Set_Union[i] != i)
	{
		vec2.push_back(i);
		i = Disjoint_Set_Union[i];
	}
	for (auto it : vec2)
	{
		Disjoint_Set_Union[it] = i;
	}
	if (i == j)
		return true;
	else
		return false;
}
//并查集find优化
int main()
{
	vector<pair<int, int>>vec =
	{
		{1,3},
		{1,2},
		{5,4},
		{2,4},
		{6,8},
		{8,7},
	};
	vector<int>Disjoint_Set_Union(9, 0);
	vector<int>rank(9, 1);

	for (int i = 0;i < 9;i++)
	{
		Disjoint_Set_Union[i] = i;
	}
	for (auto it : vec)
	{
		int i = it.first;
		int j = it.second;
		while (Disjoint_Set_Union[j] != j)
		{
			j = Disjoint_Set_Union[j];
		}
		while (Disjoint_Set_Union[i] != i)//i的循环不可以省，理论上直接插在i的孩子也可以，但是会让树的深度变深，降低查询效率
		{
			i= Disjoint_Set_Union[i];
		}
		//按秩合并
		//加权标记:期望在并查集构建过程中进行合并的时候尽量使合并后的集合树高度低一些
		//层低的挂到层高的下面   
		if (rank[i] > rank[j])
		{
			Disjoint_Set_Union[j] = i;
		}
		else if (rank[i] < rank[j])
		{
			Disjoint_Set_Union[i] = j;
		}
		else
		{
			Disjoint_Set_Union[i] = j;
			rank[j]++;
		}
	}
	int i = 0;
	int j = 0;
	cin >> i >> j;
	cout << find(Disjoint_Set_Union, i, j) << endl;
	system("pause");
	return 0;
}
#endif
//并查集应用：最小生成树
//Kruskal算法:
//按照权值大小选边，选择权值最小且两个顶点属于不同树的边
//这样既可以让总体边权值最小又可以防止成环，贪心加并查集
#if 0
struct Edge
{
	Edge(int s, int e, int c) :start(s), end(e), cost(c) {};
	int start;
	int end;
	int cost;
};
const int SIZE=1000;
int parent[SIZE];
int find(int i)
{
	int temp = i;
	while (parent[i] != i)
	{
		i = parent[i];
	}
	parent[temp] = i;
	return i;
}
int main()
{
	for (int i = 0;i < SIZE;i++)
	{
		parent[i] = i;
	}
	vector<Edge>edges;
	vector<Edge>result;
	int s, e;
	int c;
	for (int i = 0;i < 10;i++)
	{
		cin >> s >> e >> c;
		edges.emplace_back(s, e, c);
	}
	for (int i = 0;i < 9;i++)
	{
		sort(edges.begin(), edges.end(), [](auto& a, auto& b)->bool {return a.cost < b.cost;});
		for (auto it : edges)
		{
			int x = find(it.start);
			int y = find(it.end);
			if(x!=y)
			{
				parent[x] = y;
				result.push_back(it);
			}
		}
	}
	for (auto it : result)
	{
		cout << it.start << " " << it.end << " " << it.cost << endl;
	}
	system("pause");
	return 0;
}
#endif

//prim算法，注重节点，每一轮都从已加入集合通向未加入集合的所有边里，选权值最小的一条；
#if 0
#include<queue>
const int SIZE =100;
struct Edge
{
	Edge(int s, int e, int c) :start(s), end(e), cost(c) {};
	bool operator>(const Edge& a)const
	{
		return cost > a.cost;
	}
	int start;
	int end;
	int cost;
};
const int INF = INT_MAX;
int main()
{
	vector<vector<int>>graph =
	{
		{ INF, 6, 1, 5, INF, INF },
		{ 6, INF, 5, INF, 3, INF },
		{ 1, 5, INF, 5, 6, 4 },
		{ 5, INF, 5, INF, INF, 2 },
		{ INF, 3, 6, INF, INF, 6 },
		{ INF, INF, 4, 2, 6, INF }
	};
	priority_queue<Edge,vector<Edge>,greater<Edge>>edges;
	vector<Edge>best;
	int visited[SIZE] = { 0 };
	visited[0] = 1;
	int start = 0;
	for (int i = 0;i < graph.size() - 1;i++)
	{
		for (int j = 0;j < graph[start].size();j++)
		{
			edges.emplace(start, j, graph[start][j]);
		}
		while(!edges.empty())
		{
			auto it = edges.top();
			if (visited[it.end])
			{
				edges.pop();
				continue;
			}
			if (it.cost == INF)
				throw"NO RESULT!";
			best.push_back(it);
			visited[it.end] = 1;
			start = it.end;
			break;
		}
	}
	for (auto it : best)
	{
		cout << it.start << " " << it.end << " " << it.cost << endl;
	}
	system("pause");
	return 0;
}
#endif
//躲避拥堵最佳路线：
//求s到t经过路线的拥堵值最大值最小
//这道题不是让求s到t的拥堵值之和最小的路径
//而是让求从s到t的所有路线中，该路线中最大拥堵值最小的路线
//那么也就是求最小生成树直到s和t是互通的，贪心思想一直选最小边就会让s和t连通时最大拥堵值最小
//输出最大拥挤度，当st连接上的时候就退出说明最后一条边是st的必经边，那么这条边的边权值就是所选最大的，也是最小的最大值