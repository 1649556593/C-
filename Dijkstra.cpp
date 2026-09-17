#include<iostream>
using namespace std;
/*
每到一个节点，判断该节点到起点的最短路径+所连接的边权值是否比原来各点到起点的最短路径短，也就是更新最短
然后找到最小的数据，那么该顶点到起点的最短路径就确定了
因为当前这个路径是最短的,假如有绕一圈比这个更短的路径，那么那条路径的第一条权值就一定会小于当前路径，那么当前路径就不可能是最小
确定之后再更新也就是看当前选出的这个最短的基础上是否能让其他路径更短，因为当前这条路是要比直接到别的顶点的路短的，
有可能通过这个路可以更短的到达别的顶点，也就是别的顶点有更短的路径
*/
#include<vector>
#include<queue>
#include<functional>
using uint = unsigned int;
const uint INF = INT_MAX;
int Dijkstra(vector<vector<uint>>& graph, int start, int end)
{
	vector<uint>distance(graph.size(),0);
	vector<bool>isFinished(graph.size(), false);
	isFinished[start] = true;
	for (int i = 0;i < graph.size();i++)
	{
		distance[i] = graph[start][i];
	}
	for (int i = 1;i < graph.size();i++)
	{
		int index = 1;
		int min = INT_MAX;
		for (int j = 1;j < graph.size();j++)
		{
			if (!isFinished[j]&&distance[j] < min)
			{
				min = distance[j];
				index = j;
			}
		}
		isFinished[index] = true;
		for (int j = 1;j < graph.size();j++)
		{
			if (!isFinished[j]&&distance[index] + graph[index][j] < distance[j])
			{
				distance[j] = distance[index] + graph[index][j];
			}
		}
	}
	return distance[end];
}
int Dijkstra2(vector<vector<uint>>& graph, int start, int end)
{
	using con = pair<uint, int>;
	using que = priority_queue<con,vector<con>,greater<con>>;	
	que unuse;
	vector<uint>distance(graph.size(), 0);
	vector<bool>isFinished(graph.size(), false);
	for (int i = 0;i < graph.size();i++)
	{
			unuse.emplace(graph[start][i], i);
			distance[i] = graph[start][i];
	}
	unuse.pop();
	while (!unuse.empty())
	{
		pair<uint, int>temp = unuse.top();
		int k = temp.second;
		int min = temp.first;
		isFinished[k] = true;
		unuse.pop();
		if (min == INF)
		{
			break;
		}
		distance[k] = min;
		for (int i = 0;i < graph.size();i++)
		{
			if (!isFinished[i] && min + graph[k][i] < distance[i])
			{
				distance[i] = min + graph[k][i];
				unuse.emplace(distance[i], i);
			}
		}
	}
	return distance[end];
}
#if 0
int main()
{
	vector<vector<uint>> graph =
	{
		{0,6,3,INF,INF,INF},
		{6,0,2,5,INF,INF},
		{3,2,0,3,4,INF},
		{INF,5,3,0,2,3},
		{INF,INF,4,2,0,5},
		{INF,INF,INF,3,5,0}
	};
	int distance = Dijkstra(graph, 0, 4);
	int distance2 = Dijkstra2(graph, 0, 4);
	cout << distance << endl;
	cout << distance2 << endl;

	system("pause");
	return 0;
}
#endif 
