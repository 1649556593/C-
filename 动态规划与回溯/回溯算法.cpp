#include<iostream>
#include<vector>
using namespace std;
/*
子集树
*/
#if 0
void func(int arr[], int i, int length, int x[])
{
	if (i == length)
	{
		for (int j = 0;j < length;j++)
		{
			if(x[j] == 1)
				cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		x[i] = 1;
		func(arr, i + 1, length, x);

		x[i] = 0;
		func(arr, i + 1, length, x);
	}
}
int main()
{
	int arr[] = { 1,2,3 };
	int x[3] = { 0 };
	int i = 0;
	int length = sizeof(arr) / sizeof(int);
	func(arr, i, length, x);
}
#endif
#if 0
int arr[] = { 12,6,7,11,16,3,9 };
int total = 0;
const int length = sizeof(arr) / sizeof(int);
int x[length] = { 0 };
vector<int> v;
vector<int>v2;
int sum = 0;
int minres = INT_MAX;
void func(int i)
{
	if (minres == 0)
		return;
	if (i == length)
	{
		int tempmin = abs(64 - sum - sum);
		if (tempmin < minres)
		{
			minres = tempmin;
			v2.clear();
			v2 = v ;
		}
	}
	else
	{
		v.push_back(arr[i]);
		sum += arr[i];
		func(i + 1);

		v.pop_back();
		sum -= arr[i];
		func(i + 1);
	}
}
int main()
{
	func(0);
	cout << minres << endl;
	for (auto it : v2)
	{
		cout << it << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}
#endif
#if 0
int arr[] = { 12,6,7,11,16,3,9 ,8};
const int length = sizeof(arr) / sizeof(int);
vector<int>x;
vector<int>best;
int sum1 = 0;
int sum2 = 0;
int minres = INT_MAX;
int cnt = 0;
void func(int i)
{
	if (i == length && x.size()==length/2)
	{
		int tempmin = abs(sum1-sum2);
		if (tempmin < minres)
		{
			minres = tempmin;
			best.clear();
			best = x;
		}
		cnt++;
	}
	else
	{
		if (x.size() < length / 2)
		{
			sum1 += arr[i];
			sum2 -= arr[i];
			x.push_back(arr[i]);
			func(i + 1);

			sum1 -= arr[i];
			sum2 += arr[i];
			x.pop_back();
		}
		if (x.size() + length - i >= length / 2)
		{
			func(i + 1);
		}
		else
		{
			return;
		}
	}
}
int main()
{
	for (int it : arr)
	{
		sum2 += it;
	}
	func(0);
	cout << minres << endl;
	for (auto it : best)
	{
		cout << it << " ";
	}
	cout << endl;
	cout << cnt << endl;
	return 0;
}
#endif
#if 0
int arr[] = { 4,8,12,16,7,9,3 };
const int length = sizeof(arr) / sizeof(int);
int sum = 0;
int r = 4+8+12+16+7+9+3;
int res = 20;
vector<vector<int>>x;
vector<int>temp;
void func(int i)
{
	if (i == length)
	{
		if (sum == res)
		{
			x.push_back(temp);
		}
	}
	else
	{
		r -= arr[i];//注意区分未选择数字的和，与未处理的数字的和
		if (sum + arr[i] <= res)
		{
			sum += arr[i];
			temp.push_back(arr[i]);
			func(i + 1);

			sum -= arr[i];
			temp.pop_back();
		}
		if (sum + r >= res)
		{
			func(i + 1);
		}
		r += arr[i];
	}
}

int main()
{
	func(0);
	for (auto it : x)
	{
		for (auto i : it)
		{
			cout << i << " ";
		}
		cout << endl;
	}
	return 0;
}
#endif
#if 0
//该写法不再关注叶子节点，在路上达到number也算
int arr[] = { 4,8,12,16,7,9,3 };
const int length = sizeof(arr) / sizeof(int);
int number = 18;
vector<int>vec;
void func(int i, int number)
{
	if (number == 0)
	{
		for (int j : vec)
		{
			cout << j << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i;k < length;k++)
		{
			if (number >= arr[k])
			{
				vec.push_back(arr[k]);
				//func(k+1,number-arr[k]);表示不可以有重复数字
				func(k , number - arr[k]);//可以有重复数字
				vec.pop_back();
			}
		}
	}
}
int main()
{
	func(0, number);
	return 0;
}
#endif
#if 0
/*
01背包问题
*/
int w[] = { 12,5,8,9,6 };
int v[] = { 9,2,4,7,8 };
int length = sizeof(w) / sizeof(int);
int c = 20;
int sumv;
vector<int> vec;
vector<int> maxvec;
int maxv = INT_MIN;
void func(int i, int cur_c)
{
	if (cur_c >= 0)
	{
		if (sumv > maxv)
		{
			maxv = sumv;
			maxvec.clear();
			maxvec = vec;
		}
	}
	if (i == length) 
		return;
	for (int k = i;k < length;k++)
	{
		if (cur_c >= w[k])
		{
			sumv += v[k];
			vec.push_back(w[k]);
			func(k, cur_c - w[k]);
			vec.pop_back();
			sumv -= v[k];
		}
	}
}
int main()
{
	func(0, 20);
	cout << maxv << endl;
	for (int it : maxvec)
	{
		cout << it << " ";
	}
	cout << endl;
	return 0;
}
#endif 
/*
排列树
*/
#if 0
int arr[] = { 1,2,3,4 ,5,6,7,8};
int length = sizeof(arr) / sizeof(int);
vector<int>vec;
void swap(int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
void func(int i)//i表示的是第几个数字已经确定
{
	if (i == length)
	{
		for (auto it : vec)
		{
			cout << it << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i;k < length;k++)
		{
			swap(i, k);
			vec.push_back(arr[i]);
			func(i + 1);
			vec.pop_back();
			swap(i, k);
		}
	}
}
int main()
{
	func(0);
	return 0;
}
#endif
#if 0
bool judge(int arr[], int i)
{
	for (int j = 0;j < i;j++)
	{
		if (i==j || arr[i] == arr[j] || abs(arr[i] - arr[j]) == i - j)//第三个表示列数差和行数差相等，也就是在同一斜线上
		{
			return false;
		}
	}
	return true;
}
void swap(int i, int j,int arr[])
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
void func(int arr[], int i, int length)
{
	if (i == length)
	{
		for (int j=0;j<length;j++)
		{
			cout << arr[j] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int k = i;k < length;k++)
		{
			swap(i, k,arr);
			if(judge(arr,i))
				func(arr, i + 1, length);
			swap(i, k, arr);
		}
	}
}
int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8 };
	int n = 8;
	func(arr, 0, 8);
	return 0;
}
#endif
#if 0
/*
排序树的另一种实现方式
*/
int arr[] = { 1,2,3,4 };
const int length = sizeof(arr) / sizeof(int);
vector<int>vec;
int state[length] = { 0 };
void func(int i)
{
	if (i==length)
	{
		for (int it : vec)
		{
			cout << it << " ";
		}
		cout << endl;
	}
	else
	{
		for (int j = 0;j < length;j++)
		{
			if (state[j] == 0)
			{
				vec.push_back(arr[j]);
				state[j] = 1;
				func(i + 1);
				vec.pop_back();
				state[j] = 0;
			}
		}
	}
}
int main()
{
	func(0);
	return 0;
}
#endif