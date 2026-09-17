#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
//冒泡排序：稳定的排序，O(n²),最好O(n),最差O(n²)
void BubbleSort(int* arr,int sz)
{
	for (int i = 0; i < sz - 1 ; i++)
	{
		for (int j = 0; j < sz - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
//选择排序：不稳定的排序，O(n²),最好O(n²),最差O(n²)
void SelectSort(int* arr, int sz)
{
	for (int i = 0; i < sz - 1; i++)
	{
		int min = INT16_MAX;
		int index = -1;
		for (int j = i; j < sz; j++)
		{
			if (arr[j] < min)
			{
				min = arr[j];
				index = j;
			}
		}
		int temp = arr[index];
		arr[index] = arr[i];
		arr[i] = temp;
	}
}




//插入排序：基础排序中，插入排序>选择排序>冒泡排序, 稳定的排序，最差O(n²)，最好O(n)
//如果数据趋于有序，那么插入排序是所有排序算法中效率最高的算法
//原理是一个一个遍历数据，然后插入到前面已经排序好的序列中
//从后向前遍历，如果比当前数据大就向后挪，遇到小于等于的就直接跳出去
void InsertSort1(int* arr, int sz)
{
	for (int i = 1; i < sz; i++)
	{
		int val = arr[i];
		int j = i - 1;
		for (; j >= 0; j--)
		{
			if (arr[j] > val)  
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j+1] = val;
	}
}
void InsertSort2(int* arr, int sz)
{
	for (int i = 1; i < sz; i++)
	{
		int val = arr[i];
		int index = i;
		for (int j=i-1; j >= 0; j--)
		{
			if (arr[j] > val)
			//注意此处不能和arr[i]进行比较，因为arr[i]的值早就改变了
			//必须用val进行比较
			{
				arr[j + 1] = arr[j];
				index = j;
				//此处必须进行index的更新，因为如果找不到比这个数据更小的，就不会
				//进入第二个判断，index就不会更新，而val应该放在第一个位置上，因此需要更新index；
			}
			else
			{
				index = j + 1;
				break;
			}
		}
		arr[index] = val;
	}
}



//希尔排序
//时间复杂度O(n的1.3次方),最差也是O(n²)不稳定的排序
//如果数据趋于有序，那么插入排序是所有排序算法中效率最高的算法
//希尔排序就是让数据全局上尽快做到趋于有序
//希尔排序就是分组进行插入排序,每次分组都让数据趋于有序
//越到后面排序效率越高
void ShellSort(int* arr, int sz)
{
	for (int gap = sz / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < sz; i++)
		{
			int val = arr[i];
			int index = i;
			for (int j = i - gap; j >= 0; j -= gap)
			{
				if (arr[j] > val)
				{
					arr[j + gap] = arr[j];
					index = j;
				}
				else
				{
					index = j + gap;
					break;
				}
			}
			arr[index] = val;
		}
	}
}




//快速排序：
//本质上也是一种二分排序,不稳定排序
//选取基准，把比基准小的放左边，比基准大的放右边
//从right开始，如果比基准大就--，比基准小就和left交换
//依此往复，当left==right的时候就是pivot的位置
//然后进入递归
//每一层pivot放中间是O(n)，最好的情况有O(logn)层，最坏的情况是O(n)层
//所以最好的时间复杂度O(nlogn)，最坏是O(n²)，综合为O(nlogn),空间复杂度是O(logn)~O(n);
int partition(int* arr, int left, int right)
{
	int pivot = arr[left];
	while (left < right)
	{
		while (arr[right] > pivot && left < right)
		{
			right--;
		}
		arr[left] = arr[right];
		//此处虽然交换之后arr[left]并不需要判断但也不能加加，因为可能是因为left>=right才导致的跳出循环
		//这种情况会导致left错误加加
		while (arr[left] <= pivot && left < right)
		{
			left++;
		}
		arr[right] = arr[left];
	}
	arr[left] = pivot;
	return left;
}
void QuickSort(int* arr, int left, int right)
{
	if (left >= right)
		return;//含有递归的函数必须必须必须要有停止的判断条件
	int pos = partition(arr, left, right);
	QuickSort(arr, left, pos - 1);
	QuickSort(arr, pos + 1, right);
}
//快速排序算法优化
//1.在快排过程中，数据趋于有序，而数据趋于有序时，插入排序效率最高
//在一定范围内可以用插入排序代替快速排序
//2.三数取中法找合适基准数
void QuickSort2(int* arr, int left, int right)
{
	if (left >= right)
		return;//含有递归的函数必须必须必须要有停止的判断条件
	if (right - left <= 100)
	{
		//InsertSort();
		return;
	}
	int pos = partition(arr, left, right);
	QuickSort2(arr, left, pos - 1);
	QuickSort2(arr, pos + 1, right);
}
//2.三数取中法找合适基准数
int partition2(int* arr, int left, int right)
{
	int pivot = arr[(left+right)/2];
	int temp = arr[(left + right) / 2];
	arr[(left + right) / 2] = arr[left];
	arr[left] = temp;

	while (left < right)
	{
		while (arr[right] > pivot && left < right)
		{
			right--;
		}
		arr[left] = arr[right];
		//此处虽然交换之后arr[left]并不需要判断但也不能加加，因为可能是因为left>=right才导致的跳出循环
		//这种情况会导致left错误加加
		while (arr[left] <= pivot && left < right)
		{
			left++;
		}
		arr[right] = arr[left];
	}
	arr[left] = pivot;
	return left;
}


//归并排序
//最好和最坏都是O(nlogn)，空间复杂度O(n)+O(logn)；
//在归的过程中进行数据合并达到排序的效果
//额外的内存空间把两个小段有序的序列合并成大段有序的序列
//不断地递直到只剩下一个元素，然后归到上一层，上一层就有left和right还有mid的数据
//这样从每一层都做到有序，归到上一层之后，再根据left right mid值进行有序合并
void Merge(int* arr, int left, int mid, int right)
{
	int* brr = new int[right-left+1];//临时开辟和释放会使用大量时间，可以提前开辟好大片内存供使用
	int i = left;
	int j = mid + 1;
	int index = 0;
	while (i <= mid&&j<=right)
	{
		if (arr[i] < arr[j])
		{
			brr[index++] = arr[i++];
		}
		else
		{
			brr[index++] = arr[j++];
		}
	}
	while (i <= mid)
	{
		brr[index++] = arr[i++];
	}
	while (j <= right)
	{
		brr[index++] = arr[j++];
	}
	int m = 0;
	for (int k = left; k <= right; k++)
	{
		arr[k] = brr[m++];
	}
	delete[] brr;
}
void MergeSort(int* arr, int left, int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	MergeSort(arr, left, mid);
	MergeSort(arr, mid + 1, right);
	Merge(arr, left, mid, right);
}
void MergeSort(int* arr, int sz)
{
	MergeSort(arr, 0, sz - 1);
}


//堆排序
//二叉堆
//逻辑上是一颗完全二叉树：最后一层叶子节点靠左排列，而且每一层都是满的
//大根堆小根堆
//大根堆：0<=i<=(n-1)/2范围里arr[i]>arr[2*i+1]&&arr[i]>arr[2*i+2];
//小根堆：0<=i<=(n-1)/2范围里arr[i]<arr[2*i+1]&&arr[i]<arr[2*i+2];
//入堆，元素加在末尾然后对父节点进行判定                即上浮调整
//出堆，出堆顶元素用末尾元素覆盖                        即下沉调整
//空间复杂度O(1),时间复杂度O(nlogn)

//补充：
/*
function本质上是一种类，在定义了返回值和传入参数类型之后，这个类可以包含所有满足这个返回值和传入参数类型的函数
所以通过类创建对象之后，每个对象都可以有不同的实现，只要满足这个返回值和传入参数类型即可，比如function<bool(int,int)>，
可以通过两个实例化对象实现比较大小取大和取小两种函数

using的作用：
1.对类型进行重命名，如using Comp=function<bool(int,int)>
2.引入命名空间，如using namespace std；但这个命名空间几乎包含了C++所有标准库的名字，全部一次性引入容易造成命名空间污染
比如键值对pair，如果有一个自定义函数也叫pair就会造成冲突歧义，因此在使用时不推荐把std一次性引入，可以写成using std::list
std只是包含命名但不包含函数声明和实现，因此要搭配#include<list>一起使用
3.类或结构体的继承，父类中private的成员子类是无法访问的，但如果在子类中写using 父类名::具体函数，就可以提升为公有进行使用

function使用：
1.普通函数
bool cmp(int a, int b) { return a > b; }
function<bool(int, int)> f1 = cmp; // 直接装普通函数
2.Lambda表达式
function<bool(int, int)> f2 = [](int a, int b) { return a < b; }; // 装lambda
3.自定义仿函数（重载了()运算符的类）
struct MyCmp 
{
	bool operator()(int a, int b) { return a % 2 < b % 2; }
};
function<bool(int, int)> f3 = MyCmp(); // 装仿函数

Lambda
C++里的Lambda表达式，本质是编译器自动生成的匿名仿函数（函数对象）
Lambda的完整格式是[捕获列表](参数列表) -> 返回类型 {函数体}
Lambda本质就是临时的匿名函数，核心特点就是「用完即走、不需要命名、只在需要的场景里临时存在」
部分	作用（通俗版）	必选/可选
[捕获列表]	最核心的部分，决定Lambda能不能用外部变量、以及用的方式（值拷贝/直接引用）	  ✅ 必选
(参数列表)	和普通函数一样，写要传入的参数，比如(int a, int b)，无参数可以省略成()	      ⭕ 可选
-> 返回类型	指定返回值类型，编译器会自动推导（比如只有一个return语句时），90%场景不用写	  ⭕ 可选
{函数体}	写具体的执行逻辑，比如return a % 10 < b % 10;，就是你之前快排的比较规则	      ✅ 必选
1.[]  空捕获：不访问任何外部变量，是纯独立的函数，比如[]{cout << "Hello";}
2.[=] 值捕获：把所有用到的外部变量都拷贝一份，Lambda里用的是副本，不会修改原变量，是最安全的写法
3.[&] 引用捕获：直接用外部变量的原对象，Lambda里修改会同步到原变量，但要注意：如果Lambda脱离当前作用域（比如存到容器里、传给异步任务），原变量销毁后会变成悬空引用，容易出bug
4.[a, &b] 混合捕获：精准指定，a用值拷贝、b用引用，是工业界最推荐的写法，兼顾安全和灵活
只有当Lambda函数体内，要用到「不在自己形参列表里、定义在Lambda外层作用域的外部变量」时，才需要在捕获列表里写明对应的捕获规则。
*/


#include<functional>
//优先级队列
using comp = function<bool(int, int)>;
class PriorityQueue
{
public:
	PriorityQueue(int cap = 20,comp comp=greater<int>()) :size_(0), cap_(cap), comp_(comp)
	{
		que_ = new int[cap_];
	}
	~PriorityQueue()
	{
		delete[] que_;
		que_ = nullptr;
	}
	void SiftUp(int i,int val)
	{
		while (i > 0)
		{
			int father = (i - 1) / 2;
			if (comp_(val,que_[father]))
			{
				que_[i] = que_[father];
				i = father;
			}
			else
			{
				break;
			}
		}
		que_[i] = val;
	}
	void expend(int cap)
	{
		int* arr = new int[cap];
		memcpy(arr, que_, cap_ * sizeof(int));
		delete[] que_;
		cap_ = cap;
		que_ = arr;
	}
	void SiftDown(int i, int val)
	{
		while (i <= (size_ - 2) / 2)
		{
			int left = 2 * i + 1;
			int right = 2 * i + 2;
			int son = left;
			if (right<size_&& comp_(que_[right], que_[left]))
			{
				son = right;
			}
			if (comp_(que_[son], val))
			{
				que_[i] = que_[son];
				i = son;
			}
			else
			{
				break;
			}
		}
		que_[i] = val;
	}
	void push(int val)
	{
		if (size_ == 0)
		{
			que_[size_++] = val;
			return;
		}
		if (size_ == cap_)
		{
			expend(2 * size_);
		}
		SiftUp(size_,val);
		size_++;
	}
	void pop()
	{
		if (size_ == 0)
		{
			throw"Priorityqueue is empty!";
		}
		SiftDown(0,que_[size_-1]);
		size_--;
	}
	bool empty() { return size_ == 0; }
	int size() { return size_;  }
	int top() 
	{
		if (size_ == 0)
			throw"PRIORITY IS EMPTY!";
		return que_[0];
	}
private:
	int* que_;
	int size_;
	int cap_;
	comp comp_;
};

//堆排序
//时间复杂度O(nlogn)空间复杂度O(1)，不稳定的排序
void siftDown(int i, int size,int*arr)
{
	int val=arr[i];
	while (2 * i + 1 < size)//注意此处不能用（size-2）/2因为size是从大到小变化的，当size=2,1或0的时候结果都等于0所以
	{
		int left = 2*i+1;
		int right = 2 * i + 2;
		int index = left;
		if (right<size && arr[right]>arr[left])
		{
			index = right;
		}
		if (val < arr[index])
		{
			arr[i] = arr[index];
			i = index;
		}
		else
		{
			break;
		}
	}
	arr[i] = val;
}
void HeapSort(int* arr, int size)
{
	//第一次调整
	/*
	`			siftDown`下沉调整的前提是当前节点的左右子树已经是堆。从后往前，
				先处理下层子树，保证处理父节点时左右子树已经满足堆性质。
				如果从根向后处理，子树尚未调整，不满足下沉的前提条件，无法构建出正确堆。
	    1		一次调整完之后，不会再对已经调整过的结点进行调整，如果下面不是合法的堆
	   / \		那么下沉之后会把整体不合法的堆抬高，没有起到调整堆的效果
	  3   2		不能采取上浮也是因为初始非叶子结点不一定是有效堆
	 /			
	4
	*/
	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		siftDown(i, size, arr);
	}
	int remain = size;
	for (int i = 0; i < size ; i++)
	{
		int temp = arr[0];
		arr[0] = arr[remain - 1];
		arr[remain - 1] = temp;
		remain--;
		siftDown(0, remain,arr);
	}
}

//高级排序
//快排>归并>希尔>堆排序
//不管快排还是归并遍历元素都是按顺序便利的，对CPU缓存友好，CPU缓存命中率高，
//CPU在计算过程中会同时将可能会用到的数据放在缓存中，从缓存中提取比从内存中提取更快
//而堆排序是按父子结点关系访问不是按顺序，对CPU缓存不友好
//堆排序过程中进行元素下沉调整中进行的无效比较过多,末尾元素本来就小，从堆顶下沉会下沉很多，无用功太多
//在基本趋于有序的时候快排的时间复杂度会趋于O(n²)

//STL中的sort算法，当待排序列元素个数<=32时直接调用插入排序
//当递归层数过深时，函数开销变大，甚至栈内存溢出，转成堆排序
//复杂度恶化时选用三数取中法选取基准数




//基数排序 （桶排序）
//1.找出最长位数的数字，确定要处理的桶排序躺数
//2.依次由个位开始处理，把相应位数上的数字放入相应序号的桶
//3.按照桶的序号依次取出桶里面的数据放回原始数组
//4.处理完所有位数得到有序序列
//vector<vector<int>>
#include<vector>
void RadixSort(int* arr, int sz)
{
	int max = INT16_MIN;
	for (int i = 0; i < sz; i++)
	{
		if (abs(arr[i]) > max)
		{
			max = abs(arr[i]);
		}
	}
	int num = 0;
	while (max > 0)
	{
		num++;
		max /= 10;
	}
	vector<vector<int>>vecs;
	int mod = 10;
	int dev = 1;
	for (int i = 0; i < num;mod*=10,dev*=10, i++)
	{
		vecs.resize(20);//能处理负数
		for (int j = 0; j < sz; j++)
		{
			int index = arr[j] % mod / dev+10;
			vecs[index].push_back(arr[j]);
		}
		int k = 0;
		for (auto vec : vecs)
		{
			for (int i : vec)
			{
				arr[k++] = i;
			}
		}
		vecs.clear();
	}
}





// 排序算法属性汇总表 表格格式注释版
// 对齐排版后可以直接在控制台打印出规整的表格样式
/*
// 完整6大排序算法属性汇总表 规整表格注释版
/*
┌────────────┬──────────────────────────────────┬──────────────────┬──────────────────┬───────────────┬────────┐
│ 排序算法   │ 平均时间复杂度                  │ 最好时间复杂度   │ 最坏时间复杂度   │ 空间复杂度    │ 稳定性 │
├────────────┼──────────────────────────────────┼──────────────────┼──────────────────┼───────────────┼────────┤
│ 冒泡排序   │ O(n^2)                          │ O(n)             │ O(n^2)           │ O(1)          │ 稳定   │
├────────────┼──────────────────────────────────┼──────────────────┼──────────────────┼───────────────┼────────┤
│ 选择排序   │ O(n^2)                          │ O(n^2)           │ O(n^2)           │ O(1)          │ 不稳定 │
├────────────┼──────────────────────────────────┼──────────────────┼──────────────────┼───────────────┼────────┤
│ 插入排序   │ O(n^2)                          │ O(n)             │ O(n^2)           │ O(1)          │ 稳定   │
├────────────┼──────────────────────────────────┼──────────────────┼──────────────────┼───────────────┼────────┤
│ 希尔排序   │ 依赖不同的增量序列设置O(n^1.3)  │ O(n)             │ O(n^2)           │ O(1)          │ 不稳定 │
├────────────┼──────────────────────────────────┼──────────────────┼──────────────────┼───────────────┼────────┤
│ 堆排序     │ O(n*logn)                       │ O(n*logn)        │ O(n*logn)        │ O(1)          │ 不稳定 │
├────────────┼──────────────────────────────────┼──────────────────┼──────────────────┼───────────────┼────────┤
│ 快速排序   │ O(n*logn)                       │ O(n*logn)        │ O(n^2)           │ O(logn)~O(n)  │ 不稳定 │
├────────────┼──────────────────────────────────┼──────────────────┼──────────────────┼───────────────┼────────┤
│ 归并排序   │ O(n*logn)                       │ O(n*logn)        │ O(n*logn)        │ O(n)          │ 稳定   │
├────────────┴──────────────────────────────────┴──────────────────┴──────────────────┴───────────────┴────────┤
│ 基数排序   │ O(dn)                           │ O(dn)            │ O(dn)            │ O(n)          │ 稳定   │
└────────────┴──────────────────────────────────┴──────────────────┴──────────────────┴───────────────┴────────┘
*/

//内排序
//外排序：内存小数据量大，只有归并排序可以用在磁盘排序上
//1.创建十一个文件，src01-src11.txt
//2.循环读取原始文件，没读出一个数据轮询放进每一个小文件中
//3.分别把每个小文件数据都加载到内存上，进行排序完成后把排序结果写回对应小文件
//4.循环每次从src01.txt和src02.txt各读入一个整数，按归并思想选出小值写入最终的文件中，
//  循环处理直到两个文件的数字合并完成
void bubblesort(int* arr, int sz)
{
	for (int i = 0; i < sz - 1; i++)
	{
		for (int j = 0; j < sz-1-i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
void selectsort(int* arr, int sz)
{
	for (int i = 0; i < sz - 1; i++)
	{
		int min = INT32_MAX;
		int index = -1;
		for (int j = i; j < sz; j++)
		{
			if (arr[j] < min)
			{
				min = arr[j];
				index = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[index];
		arr[index] = temp;
	}
}
void insertsort(int* arr, int sz)
{
	for (int i = 1; i < sz; i++)
	{
		int val = arr[i];
		int index = i;
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[j] > val)
			{
				arr[j + 1] = arr[j];
				index = j;
			}
			else
			{
				index = j + 1;
			}
		}
		arr[index] = val;
	}
}
void shellsort(int* arr, int sz)
{
	for (int gap = sz / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < sz; i++)
		{
			int val = arr[i];
			int index = i;
			for (int j = i - gap; j >= 0; j-=gap)
			{
				if (arr[j] > val)
				{
					arr[j + gap] = arr[j];
					index = j;
				}
				else
				{
					index = j + gap;
					break;
				}
			}
			arr[index] = val;
		}
	}
}
void quicksort(int* arr, int left, int right)
{
	if (left >= right)
		return;
	int num1 = left;
	int num2 = right;
	int index = (left + right) / 2;
	int pivot = arr[index];
	int temp = arr[index];
	arr[index] = arr[left];
	arr[left] = temp;
	while (left < right)
	{
		while (arr[right] > pivot&&left<right)
		{
			right--;
		}
		arr[left] = arr[right];
		while (arr[left] <= pivot&&left<right)
		{
			left++;
		}
		arr[right] = arr[left];
	}
	arr[left] = pivot;
	quicksort(arr, num1, left - 1);
	quicksort(arr, left + 1, num2);
}
void merge(int* arr, int left, int right, int mid)
{
	int i = left;
	int j = mid + 1;
	int* brr = new int[right - left + 1];
	int k = 0;
	while (i <= mid && j <= right)
	{
		if (arr[i] <=arr[j])
		{
			brr[k++] = arr[i++];
		}
		else
		{
			brr[k++] = arr[j++];
		}
	}
	while (i <= mid)
	{
		brr[k++] = arr[i++];
	}
	while (j <= right)
	{
		brr[k++] = arr[j++];
	}
	k = 0;
	for (int i = left; i <= right; i++)
	{
		arr[i] = brr[k++];
	}
}
void mergesort(int* arr, int left, int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	mergesort(arr, left, mid);
	mergesort(arr, mid + 1, right);
	merge(arr, left, right,mid);
}

void siftdown(int* arr, int i,int sz)
{
	int val = arr[i];
	while ((2 * i + 1) < sz)
	{
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int index = left;
		if (right<sz && arr[right]>arr[left])
		{
			index = right;
		}
		if (arr[index] > arr[i])
		{
			arr[i] = arr[index];
			i = index;
		}
		else
		{
			break;
		}
	}
	arr[i] = val;

}
void heapsort(int* arr, int sz)
{
	int i = (sz - 2)/2;
	for (i; i >= 0; i--)
	{
		siftdown(arr,i,sz);
	}
	int remain = sz;
	while (remain > 0)
	{
		int temp = arr[0];
		arr[0] = arr[remain - 1];
		arr[remain - 1] = temp;
		remain--;
		siftdown(arr, 0, remain);
	}
}

void radixsort(int* arr, int sz)
{
	int max = INT16_MIN;
	for (int i = 0; i < sz; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	int num = 0;
	while (max > 0)
	{
		num++;
		max /= 10;
	}
	int mod = 10;
	int dev = 1;
	vector<vector<int>>vecs;
	for (int i = 0; i < num;mod*=10,dev*=10, i++)
	{
		vecs.resize(10);
		for (int j = 0; j < sz; j++)
		{
			int index = arr[j] % mod / dev;
			vecs[index].push_back(arr[j]);
		}
		int k = 0;
		for (auto vec : vecs)
		{
			for (int temp : vec)
			{
				arr[k++] = temp;
			}
		}
		vecs.clear();
	}
}

#if 0
int main()
{
	int arr[] = { 56,89,1,54,88,55,68,68,32,21 };
	int sz = sizeof(arr) / sizeof(int);
#if 1
	/*PriorityQueue que;
	PriorityQueue que2(20,[](int a, int b) { return a < b; });*/
	/*BubbleSort(arr, sz);*/
	/*SelectSort(arr, sz);*/
	/*InsertSort1(arr, sz);*/
	/*ShellSort(arr, sz);*/
	/*QuickSort2(arr, 0, sz - 1);*/
	/*MergeSort(arr, sz);*/
	/*for (int i : arr)
	{
		que.push(i);
	}
	for (int i : arr)
	{
		que2.push(i);
	}
	std::cout << que.top() << endl;
	que.pop();
	std::cout << que.top() << endl;
	que.pop();
	std::cout << que.top() << endl;
	que.pop();
	std::cout << que2.top() << endl;
	que2.pop();
	std::cout << que2.top() << endl;
	que2.pop();
	std::cout << que2.top() << endl;
	que2.pop();*/
	/*int COUT = 1000000;

	int* brr = new int[COUT];
	srand(time(0));
	for (int i = 0; i < COUT; i++)
	{
		brr[i] = rand();
	}
	clock_t begin, end;
	begin = clock();
	ShellSort(brr,COUT);
	end = clock();
	cout << "ShellSort spend " << (end - begin) * 0.1 / CLOCK*/
#endif
	selectsort(arr, sz);
	for (int i : arr)
	{
		cout<<i<<" ";
	}
	cout << endl;

	system("pause");
	return 0;
}
#endif

