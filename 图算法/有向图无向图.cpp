#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
/*
十字链表（有向图）
顶点结点：顶点下标，指向该顶点入边表中第一个节点（入边表信息），指向该顶点出边表中第一个节点（出边表信息）
边节点：起始顶点下标，结束顶点下标，指向终点相同的下一条边，指向起点相同的下一条边
插入边节点的时候本质上是看顶点节点，一个边节点有起始和终点，起始对应的就是起始顶点的出边，找到对应的起始顶点如果出边指针域是空，
那么出边指针域指向这个顶点，如果不是空就去该指针指向的下一个节点继续找直到为空，然后在出边指针域指向新加入的这个节点的指针，终点
则对应终点顶点的入边指针域，如果为空就加如果不为空就继续找
邻接多重链表（无向图）
顶点节点：顶点下标，firstedge
边节点：mark，ivex，ilink，jvex，jlink
插入边节点的时候本质上是看顶点节点，一个边节点无向，没有起始和终点之分，找ivex对应的顶点，如果firstedge==nullptr，那么这个指针域
就存储新加的节点指针，如果不等于就继续往后找到一个边节点，如果新加的和边节点的第一个数字相同，那么就在ilink存指针，第二个数字相同
就在jlink存,然后再找jvex
*/
//有向图邻接表
class Digraph
{
public:
	void readFile(string filepath)
	{
		FILE* pf = fopen(filepath.c_str(), "r");
		if (pf == nullptr)
		{
			throw  filepath+"not exists!";
		}
		vertics.emplace_back("");
		while (!feof(pf))
		{
			char line[1024] = { 0 };
			fgets(line, 1024, pf);
			string linestr(line);
			vertics.emplace_back(linestr.substr(0, linestr.size() - 1));
			fgets(line, 1024, pf);
			char* vers = strtok(line, ",");
			while (vers != nullptr)
			{
				if(atoi(vers)!=0)
				{
					vertics.back().adjList_.emplace_back(atoi(vers));
				}				
				vers=strtok(nullptr, ",");
			}
		}
		fclose(pf);
		
	}
	void show()
	{
		for (int i=1;i<vertics.size();i++)
		{
			cout << vertics[i].data_ << ":";
			for (auto i : vertics[i].adjList_)
			{
				cout << i << " ";
			}
			cout << endl;
		}
	}
	void dfs()
	{
		vector<bool>visited(vertics.size(),false);
		dfs(1, visited);
		cout << endl;
	}
	void bfs()
	{
		vector<bool>visited(vertics.size(), false);
		bfs(1, visited);
		cout << endl;
	}
	void shortPath1(int start, int end)
	{
		vector<bool>visited(vertics.size(),false);
		visited[start] = 1;
		int min_length=INT16_MAX;
		vector<int>path;
		path.push_back(start);
		vector<int>bestpath;
		shortPath1(start,end, visited,0, min_length,path,bestpath);
		cout << min_length << ":";
		for (auto it : bestpath)
		{
			cout << vertics[it].data_ << " ";
		}
		cout << endl;
	}
	void shortPath2(int start, int end)
	{
		vector<bool>visited(vertics.size(), false);
		vector<int>from(vertics.size(), 0);
		queue<int>que;
		que.push(start);
		visited[start] = 1;
		while (!que.empty())
		{
			int front = que.front();
			if (front == end)
			{
				break;
			}
			que.pop();
			for (auto it : vertics[front].adjList_)
			{
				if (!visited[it])
				{
					from[it] = front;
					visited[it] = 1;
					que.push(it);
				}
			}
		}
		if (!que.empty())
		{
			stack<int>s;
			int minlength=0;
			int temp = end;
			while (from[temp] != 0)
			{
				s.push(temp);
				minlength++;
				temp = from[temp];
			}
			s.push(start);
			cout << minlength << ":";
			while (!s.empty())
			{
				cout << vertics[s.top()].data_ << " ";
				s.pop();
			}
			cout << endl;
		}
		else
		{
			cout << "minPath not exsist!";
		}
	}
private:
	void shortPath1(int start,int end ,
		vector<bool>& visited,int length, int& min_length,
		vector<int>path,vector<int>&bestpath)
	{
		if (start == end)
		{
			if (length < min_length)
			{
				min_length = length;
				bestpath = path;
			}
		}
		for (auto it : vertics[start].adjList_)
		{
			if (!visited[it])
			{
				path.push_back(it);
				visited[it] = true;
				shortPath1(it,end, visited, length + 1, min_length, path, bestpath);
				visited[it] = false;
				path.pop_back();
			}
		}
	}
	void dfs(int start, vector<bool>& visited)
	{
		visited[start] = 1;
		cout << vertics[start].data_ << " ";
		for (auto it : vertics[start].adjList_)
		{
			if (visited[it] == 0)
			{
				dfs(it, visited);
			}
		}
	}
	void bfs(int start, vector<bool>&visited)
	//注意bfs在入队的时候就要标记为1，否则会导致重复入队
	{
		queue<int>que;
		que.push(start);
		visited[start] = 1;
		while (!que.empty())
		{
			int front = que.front();
			que.pop();
			cout << vertics[front].data_ << " ";
			for (auto it : vertics[front].adjList_)
			{
				if (!visited[it])
				{
					visited[it] = 1;
					que.push(it);
				}
			}
		}
	}
private:
	struct Vertic
	{
		Vertic(string data) :data_(data) {};
		string data_;
		list<int>adjList_;
	};
	vector<Vertic>vertics;
};
#if 0
int main()
{
	Digraph dg;
	dg.readFile("data.txt");
	dg.show();
	dg.dfs();
	dg.bfs();
	dg.shortPath1(1, 8);
	dg.shortPath2(1, 8);

	system("pause");
	return 0;
}
#endif