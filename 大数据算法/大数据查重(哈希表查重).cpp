#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<stdlib.h>
#include<time.h>
using namespace std;
#if 0
int main()
{
	vector<int>vec;
	srand(time(0));
	for (int i = 0; i < 10000; i++)
	{
		vec.push_back(rand() % 10000);
	}
	unordered_set<int> s1;
	for (auto key : vec)
	{
		auto it = s1.find(key);
		if (it == s1.end())
		{
			s1.insert(key);
		}
		else
		{
			cout << "key:" <<key<< endl;
			break;
		}
	}

	unordered_map<int, int>m1;
	for (int key : vec)
	{
		auto it = m1.find(key);
		if (it == m1.end())
		{
			m1.emplace(key, 1);
		}
		else
		{
			it->second++;
		}
		//等效于m1[key]++;如果key出现过就返回pair的second值的引用
		//如果key没有出现过就创建一个pair，first值为key，second值初始化为0
	}
	for (auto pair : m1)
	{
		if (pair.second >= 2)
		{
			cout << pair.first << "  " << pair.second << endl;
		}
	}
}
#endif
#if 0
int main()
{
	string src = "jjhhfgiyurtfytrs";
	unordered_map<char, int>s;
	for (auto val : src)
	{
		auto it = s.find(val);
		if (it == s.end())
		{
			s.emplace(val, 1);
		}
		else
		{
			it->second++;
		}
	}
	for (auto pair : s)
	{
		if (pair.second == 1)
		{
			cout << pair.first << endl;
			break;
		}
	}
}
#endif
#if 0
/*现有ab文件各自存放一亿条ip地址，限制内存使用100m，让找出两个文件中重复的ip地址并输出
思路：创立11个文件夹，遍历a的元素%11，也就是把文件当作哈希桶进行数据存储
      然后对b做同样的操作，那么相同的ip地址，必然会在a文件和b文件相同下标的桶里面
	  这样就可以先遍历a[n]的元素放入哈希表中然后遍历b[n]中的元素进行哈希表查重
*/
#endif