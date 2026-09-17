#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<stdlib.h>
#include<time.h>
using namespace std;
//BloomFilter说数据在，数据不一定在
//BloomFilter说数据不在，数据一定不在
//BloomFilter不存在删除操作,只支持增加查询操作
/*
具体方法：先确定一个布隆过滤器的总位数，然后不管如何处理数据最终都要%这个总位数
		  让所有数据的位数维持在这个区间，也就弥补了位图法的不足，然后再对这个处理后的数据
		  进行/和%的操作进行位图法的修改，弥补了哈希表内存占用过大的不足
BloomFilter优点：先通过多个哈希函数锁定数组下标，避免了位图法数值差过大而导致的内存浪费
，又通过数组下标中的数据进行位图法，避免了哈希表大量的空间占用，同时查询的时间复杂度也是
O(1),综合了以上两种方法的好处
缺点：会存在误判的风险
因此布隆过滤器的长度和哈希函数的个数都需要考量
使用场景：
场景一：提示过滤一些非法网站或者钓鱼网站
把所有可能怀疑有问题的网站的URL添加到布隆过滤器中
查询访问的网址在不在黑名单，如果判断存在会提示当前网站有风险禁止访问
如果网址不存在，那肯定是白名单上的合法网站
场景二：redis缓存中的应用
查key到底在不在，而且效率要求高，最好还省内存
Bloom Filter布隆过滤器
setBit(key)
getBit(key) => key不存在 => DB =》缓存redis =》返回
getBit(key) => key存在 => redis中找key
*/
#if 0
class BloomFilter
{
public:
	BloomFilter(int size = 1471)
		:bitSize_(size)
	{
		bitMap_.resize(bitSize_ / 32 + 1);
	}
public:
	void setBit(const char* str)
	{
		int idx1 = BKDRHash(str) % bitSize_;
		int idx2 = RSHash(str) % bitSize_;
		int idx3 = APHash(str) % bitSize_;

		int index = 0;
		int offset = 0;
		index = idx1 / 32;
		offset = idx1 % 32;
		bitMap_[index] |= (1 << offset);

		index = idx2 / 32;
		offset = idx2 % 32;
		bitMap_[index] |= (1 << offset);

		index = idx3 / 32;
		offset = idx3 % 32;
		bitMap_[index] |= (1 << offset);

	}
public:
	bool getBit(const char* str)
	{
		int idx1 = BKDRHash(str) % bitSize_;
		int idx2 = RSHash(str) % bitSize_;
		int idx3 = APHash(str) % bitSize_;

		int index = 0;
		int offset = 0;
		index = idx1 / 32;
		offset = idx1 % 32;
		if (bitMap_[index] & (1 << offset)==0)
		{
			return false;
		}

		index = idx2 / 32;
		offset = idx2 % 32;
		if (bitMap_[index] & (1 << offset) == 0)
		{
			return false;
		}

		index = idx3 / 32;
		offset = idx3 % 32;
		if (bitMap_[index] & (1 << offset) == 0)
		{
			return false;
		}
		return true;
	}
private:
	int bitSize_;//位图的长度（一共有多少位）
	vector<int>bitMap_;
};
//URL黑名单
class BlackList
{
public:
	void add(string url)
	{
		blockList_.setBit(url.c_str());
	}
	bool query(string url)
	{
		return blockList_.getBit(url.c_str());
	}
private:
	BloomFilter blockList_;
};

int main()
{
	BlackList list;
	list.add("http://www.baidu.com");
	list.add("http://www.360buy.com");
	list.add("http://www.tmall.com");
	string url = "http://www.baidu.com";
	cout << list.query(url) << endl;
	system("pause");
	return 0;
}
#endif