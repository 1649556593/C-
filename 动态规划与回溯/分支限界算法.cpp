/*
回溯算法采用深度优先遍历，而分支限界采用广度优先
*/
//集装箱问题：给定一定数量的集装箱和重量，给轮船的载重，问怎么样放可以让轮船实际载重更高（01背包）
#include<iostream>
#include<queue>
#include<stack>
using namespace std;
#if 0
using namespace std;
struct Node
{
	Node(int w, int h, Node* p, bool il) :weight(w), handled(h), parent(p), isLeft(il) {};
	int weight;
	int handled;
	Node* parent;
	bool isLeft;
};
int w[] = { 12,8,15 };
const int n = sizeof(w) / sizeof(w[0]);
int bestw = 0;
Node* bestwnode = nullptr;
int c = 20;
int main()
{
	queue<Node*>que;
	vector<Node*>vec;
	Node* root = new Node(0, 0, nullptr, false);
	que.push(root);
	vec.push_back(root);
	while (!que.empty())
	{
		Node* node = que.front();
		que.pop();
		int curw = node->weight;
		if (node->handled == n)
		{
			continue;
		}//和回溯算法不一样，不能到叶子节点再进行判断，因为有了容量限制和上限限制，所以不一定能走到叶子节点。
		int neww = curw + w[node->handled];
		if (neww <= c)
		{
			Node* temp = new Node(neww, node->handled + 1, node, true);
			if (neww > bestw)
			{
			bestw = neww;
					bestwnode = temp;
			}
			que.push(temp);
			vec.push_back(temp);
		}
		int sum = curw;
		for (int i = node->handled + 1;i < n;i++)
		{
			sum += w[i];
		}
		if (sum > bestw)
		{
			Node* temp = new Node(curw, node->handled + 1, node, false);
			que.push(temp);
			vec.push_back(temp);
		}
	}
	std::cout << bestw << endl;
	stack<int>s;
	Node* cur = bestwnode;
	while (cur != root)
	{
		if (cur->isLeft == true)
		{
			s.push(w[cur->handled - 1]);
		}
		cur = cur->parent;
	}
	while (!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}
	for (auto it : vec)
	{
		delete it;
	}
	std::cout << endl;
	system("pause");
	return 0;
}
#endif

#if 0
struct Node
{
	Node(int w,int v, int h, Node* p, bool il) :weight(w), value(v), handled(h), parent(p), isLeft(il) {};
	int weight;
	int value;
	int handled;
	Node* parent;
	bool isLeft;
};
int w[] = { 2,3,4,5 };
int v[] = { 4,5,6,7 };
const int n = sizeof(w) / sizeof(w[0]);
int bestv = 0;
Node* bestvnode = nullptr;
int c = 10;
int main()
{
	queue<Node*>que;
	vector<Node*>vec;
	Node* root = new Node(0, 0,0, nullptr, false);
	que.push(root);
	vec.push_back(root);
	while (!que.empty())
	{
		Node* node = que.front();
		que.pop();
		int curw = node->weight;
		int curv = node->value;
		if (node->handled == n)
		{
			continue;
		}//和回溯算法不一样，不能到叶子节点再进行判断，因为有了容量限制和上限限制，所以不一定能走到叶子节点。
		int neww = curw + w[node->handled];
		int newv = curv + v[node->handled];
		if (neww <= c)
		{
			Node* temp = new Node(neww,newv, node->handled + 1, node, true);
			if (newv > bestv)
			{
				bestv = newv;
				bestvnode = temp;
			}
			que.push(temp);
			vec.push_back(temp);
		}
		int sum = curv;
		for (int i = node->handled + 1;i < n;i++)
		{
			sum += v[i];
		}
		if (sum > bestv)
		{
			Node* temp = new Node(curw,curv, node->handled + 1, node, false);
			que.push(temp);
			vec.push_back(temp);
		}
	}
	std::cout << bestv << endl;
	stack<int>s;
	Node* cur = bestvnode;
	while (cur != root)
	{
		if (cur->isLeft == true)
		{
			s.push(w[cur->handled - 1]);
		}
		cur = cur->parent;
	}
	while (!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}
	for (auto it : vec)
	{
		delete it;
	}
	std::cout << endl;
	system("pause");
	return 0;
}
#endif

//用优先级队列实现背包问题	
#if 0
struct Node
{
	Node(int w, int v, int h, Node* p, bool il,int up) :weight(w), value(v), handled(h), parent(p), isLeft(il),upbound(up) {};
	int weight;
	int value;
	int handled;
	Node* parent;
	bool isLeft;
	int upbound;
};
int w[] = { 2,3,4,5 };
int v[] = { 4,5,6,7 };
const int n = sizeof(w) / sizeof(w[0]);
int bestv = 0;
Node* bestvnode = nullptr;
int c = 10;
int maxbound(int j, int curv)
{
	int sum = curv;
	for (int i = j;i < n;i++)
	{
		sum += v[i];
	}
	return sum;
}
class myCompare
{
public:
	bool operator()(Node* a, Node* b)const
	{
		return a->upbound < b->upbound;
	}
};
int main()
{
	priority_queue < Node*, vector<Node*>, myCompare> que;
	vector<Node*>vec;
	Node* root = new Node(0, 0, 0, nullptr, false,maxbound(0,0));
	que.push(root);
	vec.push_back(root);
	while (!que.empty())
	{
		Node* node = que.top();
		que.pop();
		int curw = node->weight;
		int curv = node->value;
		if (node->handled == n)
		{
			continue;
		}//和回溯算法不一样，不能到叶子节点再进行判断，因为有了容量限制和上限限制，所以不一定能走到叶子节点。
		int neww = curw + w[node->handled];
		int newv = curv + v[node->handled];
		if (neww <= c)
		{
			Node* temp = new Node(neww, newv, node->handled + 1, node, true,maxbound(node->handled+1,newv));
			if (newv > bestv)
			{
				bestv = newv;
				bestvnode = temp;
			}
			que.push(temp);
			vec.push_back(temp);
		}
		if (maxbound(node->handled+1,curv) > bestv)
		{
			Node* temp = new Node(curw, curv, node->handled + 1, node, false,maxbound(node->handled+1,curv));
			que.push(temp);
			vec.push_back(temp);
		}
	}
	std::cout << bestv << endl;
	stack<int>s;
	Node* cur = bestvnode;
	while (cur != root)
	{
		if (cur->isLeft == true)
		{
			s.push(w[cur->handled - 1]);
		}
		cur = cur->parent;
	}
	while (!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}
	for (auto it : vec)
	{
		delete it;
	}
	std::cout << endl;
	system("pause");
	return 0;
}
#endif