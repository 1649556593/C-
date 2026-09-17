#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using std::cout;
using std::cin;
/*
(一)线性探测法
降低哈希冲突的概率：
1.模素数
2.哈希表的装载因子loadfactor>0.75时哈希冲突概率变大，要进行扩容，原来哈希表中的元素在新的哈希表中需要重新哈希O(n)
  均摊时间复杂度是O(1);

哈希表
1.散列表 / 哈希表定义：
使关键字和其存储位置满足关系：存储位置 = f（关键字），这就是一种新的存储技术 - 散列技术。
散列技术是在记录的存储位置和它的关键字之间建立一个确定的对应关系f，使得每个关键字key对应一个存储位置f(key) 
，在查找时，根据这个确定的对应关系找到给定key的映射f(key)，如果待查找集合中存在这个记录，则必定在f(key) 的位置上。
我们把这种对应关系f称为散列函数，又称为哈希函数。采用散列技术将记录存储在一块连续的存储空间中，这块连续的存储空
间称为散列表或者哈希表（Hash Table）。

优势：适用于快速的查找，时间复杂度O(1)。100M整数 哈希表 100M * 2 = 200M 10亿个整数 4G * 2 = 8G

缺点：占用内存空间比较大。引用吴军博士的《数学之美》中所言，哈希表的空间效率还是不够高。如果用哈希表存储一亿个
垃圾邮件地址，每个email地址对应 8bytes, 而哈希表的存储效率一般只有50 % ，因此一个email地址需要占用16bytes。因此
一亿个email地址占用1.6GB，如果存储几十亿个email address则需要上百GB的内存。除非是超级计算机，一般的服务器是无法存储的。
空间换时间

散列冲突处理：
线性探测
二次探测
链地址法（链式哈希表）
*/

#if 0
enum STATE
{
	STATE_USING,
	STATE_UNUSE,
	STATE_DEL
};
class Hashtable
{
public:
	Hashtable(int tablesize = Primes_[0], double loadfactor = 0.75) :
		tablesize_(tablesize),
		loadfactor_(loadfactor),
		useBucketNum_(0),
		PrimeIdx(0)
	{
		while(tablesize > Primes_[PrimeIdx]&&PrimeIdx<PrimeSize)
		{
			PrimeIdx++;
		}
		if (PrimeIdx == PrimeSize)
		{
			PrimeIdx--;
		}
		table = new Bucket[Primes_[PrimeIdx]];
		tablesize_ = Primes_[PrimeIdx];
	}
	~Hashtable()
	{
		delete[] table;
		table = nullptr;
	}
private:
	void expend()
	{
		PrimeIdx++;
		if (PrimeIdx == PrimeSize)
			throw"table is empty!";
		Bucket* brr = new Bucket[Primes_[PrimeIdx]];
		for (int i = 0; i < tablesize_; i++)
		{
			if (table[i].state_ == STATE_USING)
			{
				int val = table[i].key_;
				int index= val % (Primes_[PrimeIdx]);
				int j = index;
				do
				{
					if (brr[j].state_ != STATE_USING)
					{
						brr[j].key_ = val;
						brr[j].state_ = STATE_USING;
						break;
					}
					j = (j + 1) % Primes_[PrimeIdx];
				} while (j != index);
			}
		}
		delete[] table;
		table = brr;
		tablesize_ = Primes_[PrimeIdx];
	}
public:
	int insert(int val)
	{
		double loadfactor = useBucketNum_*1.0 / tablesize_;
		cout << loadfactor << std::endl;
		if (loadfactor >= this->loadfactor_)
		{
			expend();
		}
		int index = val % (Primes_[PrimeIdx]);
		int i = index;
		do
		{
			if (table[i].state_ != STATE_USING)
			{
				table[i].key_ = val;
				useBucketNum_++;
				table[i].state_ = STATE_USING;
				return true;
			}
			i = (i + 1) % tablesize_;
		} while (i != index);
		return false;
	}
	bool erase(int val)
	{
		if (useBucketNum_ == 0)
		{
			throw"table is empty!";
		}
		int index = val % (Primes_[PrimeIdx]);
		int i = index;
		do
		{

			if (table[i].state_ == STATE_USING&&table[i].key_==val)
			{
				table[i].state_ = STATE_DEL;
				useBucketNum_--;
				return true;
			}
			i = (i + 1) % tablesize_;
		} while (i != index);
		return false;
	}
	bool find(int val)
	{
		if (useBucketNum_ == 0)
		{
			throw"table is empty!";
		}
		int index = val % (Primes_[PrimeIdx]);
		int i = index;
		do
		{
			if (table[i].state_ == STATE_USING && table[i].key_ == val)
			{
				return true;
			}
			i = (i + 1) % tablesize_;
		} while (i != index);
		return false;
	}
private:
	struct Bucket
	{
		Bucket(int key = 0) :key_(key), state_(STATE_UNUSE){ }
		int key_;
		STATE state_;
	};
	Bucket* table;
	int tablesize_;
	int useBucketNum_;
	double loadfactor_;

	int PrimeIdx;
	static const int PrimeSize = 10;
	static int Primes_[PrimeSize];
};
int Hashtable::Primes_[PrimeSize] = { 3,7,23,47,97,251,443,991,1471,42773 };
int main()
{
	Hashtable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);
	htable.insert(78);
	std::cout << htable.find(15) << std::endl;
	htable.erase(15);
	std::cout << htable.find(15) << std::endl;

	system("pause");
	return 0;
}
#endif

/*线性探测问题： 
1.A 在无锁探测时，依赖了一整条前后连续的桶状态；
在 A 探测完成之后、写入之前，如果是不同的桶别的线程修改了探测
路径上其他无关桶，还有可能进行扩容缩容或者消除墓碑等操作，对于
A线程又产生了影响，整个哈希表逻辑混乱。
2.还有可能A锁定之后还没锁住就切换线程对同一位置进行了修改，切回A之后
又对数据进行了覆盖，就算多加了一层判断进行保护，问题1也无法避免
3.发生哈希冲突时时间复杂度会趋向于O(n)*/
/*而链式哈希只依赖index下标指向的桶，如果两个线程指向不同的桶那毫无影响
就算两个线程指向同一个桶，依赖局部锁也可以先执行完一个后一个再执行*/
/*链式哈希桶优化:链表长度过长时可以改成红黑树存储*/

