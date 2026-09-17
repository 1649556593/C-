/*
与分治算法最大的区别是：适用于用动态规划算法求解的问题，经分解后得到的子问题往往不是互相独立的
前一个子问题的解往往为后一子问题的求解提供了有用的信息（最优子结构）
动态规划所处理的问题是一个多阶段的决策问题，一般由初始状态开始通过对中间决策的选择，达到结束状态
初始状态->决策1->决策2->.....->决策n->结束
找出最优解的性质并刻划其结构特征
递归地定义最优值
自底向上的方式计算出最优值
根据计算最优值得到的信息，构造最优解
*/
/*
硬币选择问题
*/
//1.分治算法
#if 0
int func1(int n)
{
	if (n == 1 || n == 3 || n == 5)
		return 1;
	else if (n == 2 || n == 4)
		return 2;
	else
	{
		int n1 = func1(n-1) + 1;
		int n2 = func1(n - 3) + 1;
		int n3 = func1(n - 5) + 1;
		int temp = n1 < n2 ? n1 : n2;
		return temp < n3 ? temp : n3;
		//会导致子问题重复求解降低效率
	}
}
int main()
{ 
	int val = 11;
	int num = func1(val);
	return 0;
}
#endif
#if 0
#include<iostream>
using namespace std;
int func1(int n, int dp[])
{
	if (dp[n] > 0)
		return dp[n];
	if (n == 1 || n == 3 || n == 5)
	{
		dp[n] = 1;
		return 1;
	}
	else if (n == 2 || n == 4)
	{
		dp[n] = 2;
		return 2;
	}
	else
	{
		int n1 = func1(n - 1,dp) + 1;
		int n2 = func1(n - 3,dp) + 1;
		int n3 = func1(n - 5,dp) + 1;
		int mintimes=std::min({ n1,n2,n3 });
		dp[n] = mintimes;
		return dp[n];
	}
}
int main()
{
	const int n = 18;
	int dp[n + 1] = { 0 };
	int num = func1(n, dp);
	cout << "num" << num << endl;
	return 0;
}
#endif
#if 0
//模板题，最能体现思想的写法
/*
动态规划算法的非递归方式：
从最小的开始逐级向上，先求解简单的问题然后再一级一级向上，每一级都用到前一级或者前几级的解
动态规划的递归方式
要求解最高级，那么就可以分为很多次一级的问题，通过分治思想先进入低级问题，然后一步一步根据已有解回到高级问题的求解
*/
#include<iostream>
using namespace std;
int main()
{
	const int w = 11;
	int arr[] = { 1,3,5 };
	int dp[w+1] = { 0 };
	for (int i = 1;i <= w;i++)
	{
		dp[i] = INT_MAX;
	}
	for (int i = 1;i <= w;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (i >= arr[j])
			{
				int temp = dp[i - arr[j]]+1;
				if (temp < dp[i])
					dp[i] = temp;
			}

		}
	}
	cout << dp[w] << endl;
	system("pause");
	return 0;
}           
#endif

#include<iostream>
using namespace std;
#if 0
//指定个数的斐波那契数列
int func2(int n,int dp[])
{
	if (n == 1|| n==2 )
	{
		dp[n] = 1;
		return 1;
	}
	else if (n == 3)
	{
		dp[n] = 2;
		return 2;
	}
	else
	{
		dp[n] = func2(n - 1, dp) + func2(n - 2, dp);
		return dp[n];
	}
}
int main()
{
	/*int dp[300 + 1] = { 0 };
	for (int i = 1;i <= 300;i++)
	{
		cout << func2(i,dp) << " ";
	}
	cout << endl;
	system("pause");
	return 0;*/

	//非递归实现
	long long dp1[300 + 1] = { 0 };
	dp1[1] = 1;
	dp1[2] = 1;
	for (int i = 3;i <= 300;i++)
	{
		dp1[i] = dp1[i - 1] + dp1[i - 2];
	}
	for (int i = 1;i <= 300;i++)
	{
		cout << dp1[i] << " ";
	}
	cout << endl;
	system("pause");
}
#endif

#if 0
//最大子段和
//求以每个元素结束的最大子段和
//dp[i] 的定义是"以 arr[i] 结尾的最大子段和"
int main()
{
	int arr[] = { -2,11,-4,13,-5,-2 };
	int dp[6] = { 0 };
	for (int i = 0;i < 6;i++)
	{
		dp[i] = arr[i];
		if (dp[i] < 0)
		{
			dp[i] = 0;
		}
	}
	for (int i = 1;i < 6;i++)
	{
		dp[i] = max(dp[i - 1] + arr[i], dp[i]);
	}
	int max = INT_MIN;
	for (int i = 0;i < 6;i++)
	{
		if (max < dp[i])
			max = dp[i];
	}
	cout << max << endl;
	system("pause");
	return 0;
}
#endif

#if 0
//求序列的最长非降子序列长度
//双层for循环不一定能找到最优解，如3，4，2，8，6，7，10
int main()
{
	int arr[] = { 5,3,4,1,8,7,9 };
	int dp[7];
	for (int i = 0;i < 7;i++)
	{
		dp[i] = 1;
	}
	for (int i = 1;i < 7;i++)
	{
		for (int j = 0;j < i;j++)
		{
			if (arr[i] > arr[j]&&dp[i]<dp[j]+1)
			{
				dp[i] = dp[j] + 1;
			}
		}
	}
	int max = INT_MIN;
	for (int i = 0;i < 7;i++)
	{
		if (max < dp[i])
		{
			max = dp[i];
		}
	}
	cout << max << endl;
	system("pause");
	return 0;
	//求最长子段和是从以某一个位置结尾的最长字段和，在计算下一个的时候要么接要么不接
	//而求序列的最长非降序列则是在计算下一个的时候既可以接上一个的也可以接前面的其他的
}
#endif
#if 0
//分治思想
//求两个序列公共子序列的长度
/*
LCS(X[1.....n],Y[1......m])
if(X[n]==Y[m])
{
	LCS(X[1......n-1],Y[1........m-1]);
}
else
{
	LCS(X[1......n],Y[1........m-1]);
	LCS(X[1......n-1],Y[1........m]);
}

*/
#include<string>
#include<vector>
#include<stack>
//分治算法+dp
int LCS(string str1, int end1, string str2, int end2, vector<vector<int>>&dp,int path[][7])
{
	if (end1 < 0 || end2 < 0)
		return 0;
	if (dp[end1][end2] >= 0)
	{
		return dp[end1][end2];
	}
	if (str1[end1] == str2[end2])
	{
		path[end1][end2] = 1;
		dp[end1][end2]= LCS(str1, end1 - 1, str2, end2 - 1,dp,path) + 1;
		return dp[end1][end2];
	}
	else
	{
		//合理性：当发现不一样的时候是以两个字符串分别为标准，而不是一个
		int num1 = LCS(str1, end1, str2, end2 - 1, dp,path);
		int num2 = LCS(str1, end1 - 1, str2, end2, dp, path);
		if (num1 > num2)
		{
			dp[end1][end2] = num1;
			path[end1][end2] = 2;
		}
		else
		{
			dp[end1][end2] = num2;
			path[end1][end2] = 3;
		}
		return dp[end1][end2];
	}
}
int main()
{
	string str1 = "helloworld";
	string str2 = "howoerd";
	const int sz1 = str1.size();
	const int sz2 = str2.size();
	vector<vector<int>>dp;
	dp.resize(sz1);
	for (int i = 0;i < sz1;i++)
	{
		dp[i].resize(sz2);
	}
	for (int i = 0;i < sz1;i++)
	{
		for (int j = 0;j < sz2;j++)
		{
			dp[i][j] = -1;
		}
	}
	int path[10][7];
	for (int i = 0;i < sz1;i++)
	{
		for (int j = 0;j < sz2;j++)
		{
			path[i][j] = 0;
		}
	}
	cout<<LCS(str1, sz1-1, str2, sz2-1,dp,path)<<endl;
	for (int i = 0;i < sz2;i++)
	{
		cout << "\t" << str2[i];
	}
	cout << endl;
	for (int i = 0;i < sz1;i++)
	{
		cout << str1[i];
		for (int j = 0;j < sz2;j++)
		{
			
			cout << "\t" << dp[i][j];
		}
		cout << endl;
	}
	stack<char>s;
	int i = sz1 - 1;
	int j = sz2 - 1;
	while (i>=0&&j>=0&&path[i][j]!=0)
	{
		if (path[i][j] == 1)
		{
			s.push(str1[i]);
			i--;
			j--;
		}
		else if (path[i][j] == 2)
		{
			j--;
		}
		else if (path[i][j] == 3)
		{
			i--;
		}
	}
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
	return 0;
}
#endif

#if 0
//LCS非递归实现
#include<vector>
int main()
{
	string str1 = "helloworld";
	string str2 = "howoerd";
	const int sz1 = str1.size();
	const int sz2 = str2.size();
	int n = sz1 - 1;
	int m = sz2 - 1;

	vector<vector<int>>dp;
	dp.resize(sz1+1);
	for (int i = 0;i < sz1+1;i++)
	{
		dp[i].resize(sz2+1);
	}
	for (int i = 0;i < sz1+1;i++)
	{
		for (int j = 0;j < sz2+1;j++)
		{
			dp[i][j] = 0;
		}
	}

	for (int i = 1;i <= n+1;i++)
	{
		for (int j = 1;j <= m+1;j++)
		{
			if (str1[i-1] == str2[j-1])
			{
				dp[i][j] = 1 + dp[i - 1][j - 1];
			}
			else
			{
				int len1 = dp[i - 1][j];
				int len2 = dp[i][j - 1];
				if (len1 > len2)
				{
					dp[i][j] = len1;
				}
				else
				{
					dp[i][j] = len2;
				}
			}
		}
	}
	cout << dp[sz1][sz2] << endl;
	system("pause");
	return 0;
}
#endif
#if 0
//完全背包
int main()
{
	int w[] = {2,3,4,5};
	int v[] = {3,4,5,6};
	int szw = sizeof(w) / sizeof(int);
	const int capacity = 20;
	int dp[capacity + 1] = { 0 };
	for (int i = 1;i <= capacity;i++)
	{
		for (int j = 0;j < szw;j++)
		{
			if (i >= w[j])
			{
				dp[i] = max(dp[i - w[j]] + v[j],dp[i]);
			}
		}
	}
	cout << dp[capacity] << endl;
	system("pause");
	return 0;
}


#endif
#include<stack>
#if 0
int main()
{
	//有最优子结构问题，划分的子问题非独立 
	//问题的状态
	//状态转移方程
	//dp[i][j]表示前i件商品在j的容量空间下的最优解
	//那么对于第i件商品，有两种可能，放或者不放
	//如果不放，就等效于dp[i-1][j]也就是前i-1件商品在j容量下的最优解
	//如果放，那么相应的会减少一定的容量并且获得价值，问题就成了求解dp[i-1][j-w[i-1]]+v[i-1];
	//由此，后一个问题由前一个问题得知，那么就从最小的子问题开始求解
	//dp[0][j]表示前0件商品在j的容量下的最大价值，那么全等于0
	//dp[i][0]表示前i件商品在0的容量下的最大价值，那么全等于0
#if 0
	int w[] = { 8,6,4,2,5 };
	int v[] = { 6,4,7,8,6 };
	int n = sizeof(w) / sizeof(w[0]);
	int c = 16;
	int** dp = new int* [n + 1];
	for (int i = 0;i < n + 1;i++)
	{
		dp[i] = new int[c + 1]();
	}

	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= c;j++)
		{
			if (j < w[i - 1])
			{
				dp[i][j] = dp[i - 1][j];
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
			}
		}
	}
	stack<int>s;
	int i = n;
	int j = c;
	while (i >= 1)
	{
		if (dp[i][j] == dp[i - 1][j])
		{
			i--;
		}
		else
		{
			s.push(i);
			j = j - w[i - 1];
			i--;
		}
	}
	while (!s.empty())
	{
		cout<<s.top()<<" ";
		s.pop();
	}
	cout<<endl;
	cout << dp[n][c] << endl;
	for (int i = 0;i < n + 1;i++)
	{
		delete[] dp[i];
	}
	delete[] dp;
#endif
#if 0
	//dp一维数组写法
	int w[] = { 8,6,4,2,5 };
	int v[] = { 6,4,7,8,6 };
	int n = sizeof(w) / sizeof(w[0]);
	const int c = 16;
	int dp[c + 1] = { 0 };
	int** path = new int* [n + 1];
	for (int i = 0;i < n + 1;i++)
	{
		path[i] = new int[c+1]();
	}
	for (int i = 1;i <= n;i++)
	{
		for (int j = c;j >= w[i - 1];j--)
		{
			path[i][j] = 1;
			dp[j] = max(dp[j], dp[j - w[i - 1]] + v[i - 1]);
		}
	}
	//路径回溯
	stack<int>s;
	int i = n;
	int j = c;
	while (i >= 1)
	{
		if (path[i][j] == 1)
		{
			s.push(i);
			j -= w[i - 1];
		}
		i--;
	}

	for (int i = 0;i < n + 1;i++)
	{
		delete[] path[i];
	}
	delete[] path;
	//一维数组必须是逆序的防止之前的元素已经被第二层覆盖
	cout << dp[c] << endl;
	stack<int>s;
#endif
	system("pause");
	return 0;
}
#endif
//01背包问题单个物品只可以选择一次，所以单个物品状态就只有选择和不选择，对于第i件商品，有两种可能，放或者不放
//			如果不放，dp[i][j]就等效于dp[i-1][j]也就是前i-1件商品在j容量下的最优解
//			如果放，那么相应的会减少一定的容量并且获得价值，dp[i][j]=dp[i-1][j-w[i-1]]+v[i-1];
//而完全背包问题由于单个物品可以选择无数次，在j的容量下，我需要选择的是放哪件商品（只要能放得下就一定放，不过要找到最优解）选择之后我需要的是剩余容量的最大价值






#if 0
//三角形最短路径问题
#include<vector>
int func(int i, vector<vector<int>>&v, int height,int** dp)
{
	if (dp[height - 1][i] != -1)
	{
		return dp[height - 1][i];
	}
	if (height == 4)
	{
		dp[height - 1][i] = v[height - 1][i];
		return dp[height - 1][i];
	}
	dp[height-1][i]= v[height-1][i]+min(func(i, v, height + 1,dp), func(i + 1, v, height + 1,dp));
}
int main()
{
#if 0
	vector<vector<int>> v = {
		{2},
		{3, 4},
		{6, 5, 7},
		{4, 1, 8, 3}
	};
	int** dp = new int* [v.size()];
	for (int i = 0;i < v.size();i++)
	{
		dp[i] = new int[v[v.size() - 1].size()];
		for (int j = 0; j < v[v.size() - 1].size(); j++)
		{
			dp[i][j] = -1;
		}
	}
	cout << func(0, v, 1,dp) << endl;
	for (int i = 0;i < v.size();i++)
	{
		delete[] dp[i];
	}
	delete[] dp;
#endif
	vector<vector<int>> v = {
		{2},
		{3, 4},
		{6, 5, 7},
		{4, 1, 8, 3}
	};
	int** dp = new int* [v.size()];
	for (int i = 0;i < v.size();i++)
	{
		dp[i] = new int[v[v.size() - 1].size()];
		for (int j = 0; j < v[v.size() - 1].size(); j++)
		{
			dp[i][j] = -1;
		}
	}
	
	for (int i = 0;i < v[v.size()-1].size();i++)
	{
		dp[v.size() - 1][i] = v[v.size() - 1][i];
	}

	for (int i = v.size() - 2;i >= 0;i--)
	{
		for (int j = 0;j < v[i].size();j++)
		{
			dp[i][j] = v[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
		}
	}
	cout << dp[0][0] << endl;
	for (int i = 0;i < v.size();i++)
	{
		delete[] dp[i];
	}
	delete[] dp;
	system("pause");
	return 0;
}
#endif