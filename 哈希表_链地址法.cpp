#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<vector>
using namespace std;
class HashTable
{
public:
	HashTable(int tablesize = Primes_[0], double loadfactor = 0.75) :
		useBucketNum_(0),
		loadfactor_(loadfactor),
		PrimeIdx_(0)
	{
		while (tablesize > Primes_[PrimeIdx_]&&PrimeIdx_<PrimeSize_)
		{
			PrimeIdx_++;
		}
		if (PrimeIdx_ == PrimeSize_)
		{
			PrimeIdx_--;
		}
		table_.resize(Primes_[PrimeIdx_]);
	}
private:
	void expand()
	{
		PrimeIdx_++;
		if (PrimeSize_ == PrimeIdx_)
		{
			throw"HashTable is empty!";
		}
		vector<list<int>>oldtable;
		table_.swap(oldtable);
		//如果两个容器使用的空间配置器allocator是一样的，那么直接
		//交换两个容器的成员变量即可，效率高，如果空间配置器不一样
		//那么意味着两个容器管理外部堆内存方式不一样，需要效率低的整个数据的交换
		table_.resize(Primes_[PrimeIdx_]);
		useBucketNum_ = 0;
		for (auto list : oldtable)
		{
			for (auto val : list)
			{
				int index = val % Primes_[PrimeIdx_];
				if (table_[index].empty())
				{
					useBucketNum_++;
				}
				table_[index].emplace_front(val);
			}
		}
	}
public:
	bool insert(int val)
	{
		double factor = useBucketNum_ * 1.0 / table_.size();
		//size输出的是vector容器中已经存储的数据个数
		//capacity输出的是vector容器的总容量，大于等于size
		//reserve是预留空间但不创建数据
		//resize是预留空间并且构造数据
		cout << factor << endl;
		if (factor > this->loadfactor_)
		{
			expand();
		}
		int index = val % Primes_[PrimeIdx_];
		if (table_[index].empty())
		{
			useBucketNum_++;
			table_[index].emplace_front(val);
			return true;
		}
		else
		{
			auto it = ::find(table_[index].begin(), table_[index].end(), val);
			if (it == table_[index].end())
			{
				table_[index].emplace_front(val);
				//push_front只能插入同一类型，即对于list只能插入结点不能插入数据
				//emplace_front可以直接传入元素构造所需的参数包
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	bool erase(int val)
	{
		int index = val % Primes_[PrimeIdx_];
		auto it = ::find(table_[index].begin(), table_[index].end(), val);
		if (it == table_[index].end())
		{
			return false;
		}
		else
		{
			table_[index].erase(it);
			if (table_[index].empty())
			{
				useBucketNum_--;
			}
			return true;
		}
	}
	bool find(int val)
	{
		int index = val % Primes_[PrimeIdx_];
		auto it = ::find(table_[index].begin(), table_[index].end(), val);
		return it != table_[index].end();
	}
	
private:
	vector<list<int>>table_;
	int useBucketNum_;
	double loadfactor_;

	static const int PrimeSize_ = 10;
	static int Primes_[PrimeSize_];
	int PrimeIdx_;
};
int HashTable::Primes_[PrimeSize_] = { 3,7,23,47,97,251,443,991,1483,42773 };
#if 0
int main()
{
	HashTable hstable;
	hstable.insert(18);
	hstable.insert(36);
	hstable.insert(48);
	hstable.insert(37);
	hstable.insert(54);
	hstable.insert(99);
	hstable.insert(66);
	hstable.insert(181);
	hstable.insert(182);
	hstable.insert(183);
	hstable.insert(184);
	hstable.insert(185);


	hstable.erase(54);
	std::cout << hstable.find(54) << std::endl;

	system("pause");
	return 0;
}
#endif