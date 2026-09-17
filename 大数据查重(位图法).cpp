#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<stdlib.h>
#include<time.h>
using namespace std;
//用一个位0/1来存储数据状态，比较适合状态简单，数据量大，要求内存使用率低的问题场景
/*有一亿个整数，最大值不超过一亿，问都有哪些元素重复，谁是第一个重复的，谁是第一个不重复的，内存限制100M*/

/*
位图法：
1.需要知道元素序列的最大值，根据最大值来定义bitmap位图数组
2.根据/%两个操作映射到元素对应的位
3.读取该位置的值0，1
如何把某一位置置1 bitmap[index]|(1<<offset)
如何获取该位置的值 bitmap[index]&(1<<offset)
位图法是/%两个操作后确定的位置
标准纯位图法天然就不存在哈希冲突问题
对于char型数组就是/8，对于int型数组就是/32
*/
//缺陷，数据大小相差过大，尽管数据量小，也会占用不必要的内存比如1，2，10000000000
//推荐数据个数和数据最大值相差不大的场景使用
#if 0
int main()
{
	vector<int>vec{ 12,78,90,123,8,9,89,123,90};
	int max = INT16_MIN;
	for (int i : vec)
	{
		if (i > max)
			max = i;
	}
	int size = (max / 32 + 1);
	//为什么/的一定是32或者8呢，因为如果/的是31，那么原本31/32等于0会进入数组0号下标
	//然后%32等于31使用最高位，如果改成/31，那么就会成1进入数组1号下标，0号下标中的最
	//高位也就浪费掉了如果比32更大，那么大于31的数字也可能会进入数组0号下标造成访问冲突
	int* bitmap = new int[size]();
	unique_ptr<int[]>ptr(bitmap);
		//unique_ptr<int> p(new int(10));		✅ 正确	管理单个int对象，析构调用delete
		//unique_ptr<int[]> p(new int[10]);		✅ 正确	管理10个元素的int数组，析构调用delete[]
		//auto p = make_unique<int[]>(size);	✅ 最佳实践	自动申请 + 初始化数组，无裸指针，异常安全
	//该变量出栈时会自动把对应指针的堆内存释放掉
	//找第一个重复出现的数字
	for (int i : vec)
	{
		int index = i / 32;
		int offset = i % 32;
#if 1
		if ((bitmap[index] & (1 << offset))==0)
		//注意(bitmap[index] & (1 << offset)的返回值不一定是1，而是1<<offset
		{
			bitmap[index] |= (1 << offset);
		}
		else
		{
			cout << i << endl;
		}
#endif
	}
	//如果要查询哪个数据是第一个不重复的数据，按照位图法之
	//能记录是否出现可以用两个数组，一个记录是否出现一个记录
	//是否重复出现，然后第二次遍历的时候查第二个数组
	system("pause");
}
#endif