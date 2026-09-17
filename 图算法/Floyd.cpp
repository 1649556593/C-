#include<iostream>
#include<vector>
#include<queue>
#include<functional>
using uint = unsigned int;
const uint INF = INT_MAX;
using namespace std;
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
	vector<vector<uint>>distance(graph);
	for (int k = 0;k < distance.size();k++)//中转点是谁
	{
		for (int i = 0;i < distance.size();i++)//起点是谁
		{
			for (int j = 0;j < distance.size();j++)//终点是谁
			{
				distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
			}
		}
	}
	cout << distance[0][4] << endl;
	system("pause");
	return 0;
}
#endif