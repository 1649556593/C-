//总是做出在当前看来最好的选择
//典型的就是硬币问题
//01背包和完全背包一般都不适用贪心
//部分背包适用贪心
#include<algorithm>
#include<iostream>
#include<stack>
using namespace std;
#if 0
//贪心求硬币问题
int main()
{
	int arr[] = { 1,3,5 };
	int c = 11;
	sort(arr, arr + 3, [](int a, int b)->bool {return a > b;});
	//sort(arr, arr + 3, greater<int>());
	for (int it : arr)
	{
		cout << it << " ";
	}
	cout << endl;
	int n = sizeof(arr) / sizeof(arr[0]);
	int idx = 0;
	int cnt = 0;
	while (c > 0&&idx<n)
	{
		if (c >= arr[idx])
		{
			c -= arr[idx];
			cnt++;
		}
		else
		{
			idx++;
		}
	}
	cout << cnt << endl;
	return 0;
}
#endif

#if 0
//贪心求部分背包问题
//按物品性价比放
struct Product
{
	double getPrice()const
	{
		return v * 1.0 / w;
	}
	bool operator>(const Product& p)const
	{
		return getPrice() > p.getPrice();
	}
	int id;int w;int v;
};
int main()
{
	int w[] = { 8,6,4,2,5 };
	int v[] = { 6,4,7,8,6 };
	const int n = sizeof(w) / sizeof(w[0]);
	int c = 12;
	double val = 0;
	stack<int>s;
	Product pros[n];
	for (int i = 0;i < n;i++)
	{
		pros[i].w = w[i];
		pros[i].v = v[i];
		pros[i].id = i+1;
	}
	sort(pros, pros + n, [](Product& p1, Product& p2)->bool {return p1 > p2;});
	for (int i = 0;i < n;i++)
	{
		if (c >= pros[i].w)
		{
			c -= pros[i].w;
			val += pros[i].v;
			s.push(pros[i].id);
		}
		else
		{
			val += pros[i].v * (c * 1.0 / pros[i].w);
		}
	}
	while (!s.empty())
	{
		cout << s.top() <<" ";
		s.pop();
	}
	cout << endl;
	cout << val << endl;
	return 0;
}
#endif

#if 0
//贪心算法求柜台服务问题
//每次添加找添加之后时间最少的柜台，如果添加之后导致比最短时长更大了就更新最短时长
int main()
{
	int arr[] = { 3,2,4 };
	const int m = sizeof(arr) / sizeof(arr[0]);
	int n = 15;
	sort(arr, arr + m);
	int x[m] = { 0 };
	int mintime = 0;
	for (int i = 0;i < n;i++)
	{
		int time = (x[0] + 1) * arr[0];
		int minidx = 0;
		for (int j = 1;j < m;j++)
		{
			int t= (x[j] + 1) * arr[j];
			if (t <= time)
			{
				minidx = j;
			}
		}
		x[minidx]++;
		if (x[minidx] * arr[minidx] > mintime)
		{
			mintime = x[minidx] * arr[minidx];
		}
	}
	for (int it : x)
	{
		cout << it << endl;
	}
	cout << mintime << endl;
	system("pause");
	return 0;
}

#endif

