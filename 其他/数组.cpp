#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//数组
//优点
//下标访问/随机访问：时间复杂度为O(1)!
//末尾插入或删除元素时间复杂度为O(1)
//对指针加加或减减访问元素很方便
//缺点
//无序数组查找（线性搜索）时间复杂度为O(n)
//有序（二分搜索）O(logn)
//非末尾增加或删除元素会导致大量的数据移动O(n)
class Array
{
public:
	Array(int size = 10) :mcur(0), mcap(size)
	{
		mparr = new int[mcap]();
	}
	~Array()
	{
		delete[] mparr;
		//指针指向的内存以被释放，mparr变成野指针(指针本身不为空，但是指向的地址内存已被释放)
		mparr = NULL;//防止出现野指针
	}
private:
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, mparr, sizeof(int) * mcap);
		//完全按字节复制，把源内存（src）的count个字节，原封不动搬到目标内存（dest），
		//不关心内存里存的是整数、结构体、指针还是其他类型，只处理二进制数据。 
		delete[] mparr;
		mparr = p;
		mcap = size;
	}
public:
	void show()
	{
		for (int i = 0; i < mcur; i++)
		{
			cout << mparr[i] << " ";
		}
		cout << endl;
	}
	void push_back(int val)
	{
		if (mcur == mcap)
		{
			expand(2 * mcap);
		}
		mparr[mcur++] = val;
	}
	void pop_back()
	{
		if (mcur == 0)
		{
			return;
		}
		mcur--;
	}
	void insert(int pos, int val)
	{
		if (pos<0 || pos>mcur)
		{
			throw"pos invalid";
			return;
		}
		if (mcur == mcap)
		{
			expand(2 * mcap);
		}
		for (int i = mcur; i >= pos+1; i--)
		{
			mparr[i] = mparr[i-1];
		}
		mparr[pos] = val;
		mcur++;
	}
	void erase(int pos)
	{
		if (pos < 0 || pos >= mcur)
		{
			return;
		}
		for (int i = pos; i < mcur - 1; i++)
		{
			mparr[i] = mparr[i + 1];
		}
		mcur--;
	}
	int find(int val)
	{
		for (int i = 0; i < mcur; i++)
		{
			if (mparr[i] == val)
			{
				return i;
			}
		}
		return -1;
	}

private:
	int* mparr;
	int mcap;  //数组容量
	int mcur;  //数组有效元素个数
};
//int main()
//{
//	Array arr;
//	srand(time(0));
//	for (int i = 0; i < 10; i++)
//	{
//		arr.push_back(rand() % 100);
//	}
//	arr.show();
//	arr.pop_back();
//	arr.show();
//
//	arr.insert(0, 200);
//	arr.show();
//	int pos=arr.find(200);
//	if (pos != -1)
//	{
//		arr.erase(pos);
//		arr.show();
//	}
//}
