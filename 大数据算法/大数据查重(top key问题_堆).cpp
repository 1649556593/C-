#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<stdlib.h>
#include<time.h>
#include<queue>
#include<functional>
using namespace std;
//从已知序列中求最小的三个元素
//需要一个大根堆(要几个元素就放几个元素)：把大根堆堆顶的大值不断淘汰，放入小值然后调整
//相当于先放了三个待选项，一定优先淘汰最大的，所以采用大根堆淘汰堆顶的方法
//从已知序列里求最大的三个元素
//需要一个小根堆(要几个元素就放几个元素)：把小根堆堆顶的小值不断淘汰，放入大值然后调整
//时间复杂度为O(n)
#if 0
int main()
{
	srand(time(0));
	vector<int> vec;
	for (int i = 0; i < 10000; i++)
	{
		vec.push_back(rand() % 10000);
	}
	//求vec中最小的5个元素
	priority_queue<int>maxheap;
	int k = 5;
	for (int i = 0; i < 5; i++)
	{
		maxheap.push(vec[i]);
	}
	for (int i = 5; i < vec.size(); i++)
	{
		if (vec[i] < maxheap.top())
		{
			maxheap.pop();
			maxheap.push(vec[i]);
		}
	}
	while (!maxheap.empty())
	{
		cout << maxheap.top() << " ";
		maxheap.pop();
	}
	cout << endl;
	
	priority_queue<int, vector<int>, greater<int>>minheap;
	k = 5;
	for (int i = 0; i < 5; i++)
	{
		minheap.push(vec[i]);
	}
	for (int i = 5; i < vec.size(); i++)
	{
		if (vec[i] > minheap.top())
		{
			minheap.pop();
			minheap.push(vec[i]);
		}
	}
	while (!minheap.empty())
	{
		cout << minheap.top() << " ";
		minheap.pop();
	}
	cout << endl;

	system("pause");
	return 0;
}
#endif
#if 0
int main()
{
	//统计重复出现次数最少的三个数字
	srand(time(0));
	unordered_map<int,int> um;
	for (int i = 0; i < 10000; i++)
	{
		int num = rand() % 1000;
		auto it = um.find(num);
		if (it == um.end())
		{
			um.emplace(num,0);
		}
		else
		{
			(it->second)++;
		}
	}
	using Type = pair<int, int>;
	using Comp = function<bool(Type&, Type&)>;
	priority_queue<Type, vector<Type>, Comp> maxheap([](Type& a, Type& b) { return a.second < b.second; });
	//创建的 Comp 算是一个类，这个类可以囊括所有返回值类型和参数满足 <bool (Type&,Type&)> 
	//的函数对象，然后后面（）里的实际上就是一个符合要求的匿名函数对象,是在含参构造中传入的实例化对象
	//lambda表达式实际上就是临时匿名对象，他在创建的时候就有一个独一无二的匿名类，通过decltype(lam)来获取这个匿名类
#if 0
	auto lam = [](Type& a, Type& b) { return a.second < b.second; };
	priority_queue<Type, vector<Type>, decltype(lam)> heap(lam);
#endif
	//本质上priority_queue的第三个参数就是要一个可以比较的类，用仿函数也完全可以
#if 0
	class Comp
	{
	public:
		bool operator()(pair<int, int>& p1, pair<int, int>& p2)
			return p1.second < p2.second;
	};
	priority_queue<Type, vector<Type>, Comp> maxheap;
#endif
	for (int i = 0; i < 3; i++)
	{
		auto it = um.begin();
		maxheap.push(*it);
		um.erase(it);
	}
	for (auto it : um)
	{
		if (it.second < maxheap.top().second)
		{
			maxheap.pop();
			maxheap.push(it);
		}
	}
	while (!maxheap.empty())
	{
		cout << maxheap.top().first<<" ";
		cout << maxheap.top().second << endl;
		maxheap.pop();
	}
	system("pause");
	return 0;
}
#endif