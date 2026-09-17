#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;
//数组每个元素内存连续，内存碎片化容易导致大内存数组创建失败
//链表每个节点内存独立分配,可以提高内存利用率
//插入删除不需要移动其他节点，时间复杂度为O(1);
//不需要进行专门的扩容操作

//缺点：
//内存占用量大，每一个节点多出存放地址的空间
//节点内存不连续不可以随机访问
//链表搜索效率不高只能从头节点开始逐节点遍历

//链表搜索O(n)，链表删除O(1)

//C A P定理：一致性，可用性，分区容错性（分布式系统）

//开堆区内存就要用指针接收，因此操作每个节点用的都是指针
//单链表实现
struct Node
{
	Node(int data = 0) :data_(data), next_(nullptr) {};
	int data_;
	Node* next_;
};
class Clink
{
public:
	Clink()
	{
		head_ = new Node();
	}
	~Clink()
	{
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;//类似于创建临时变量
			delete p;
			p = head_;
		}
	}
public:
	void InsertTail(int val)
	{
		Node* node = new Node(val);
		Node* temp = head_;
		while (temp->next_ != nullptr)//NULL本质上是整数零，nullptr就是类型安全的空指针关键字
			//用下一个节点判断是因为要找的是最后一个节点，最后一个节点的特征就是下一个节点是空
		{
			temp = temp->next_;
		}
		temp->next_ = node;
	}
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
	}
	void Remove(int val)
	{
		Node* temp = head_->next_;
		Node* pre = head_;
		while (temp != nullptr)
		{
			if (temp->data_ == val)
			{
				pre->next_ = temp->next_;
				delete temp;
				return;
			}
			else
			{
				temp = temp->next_;
				pre = pre->next_;
			}
		}
	}
	void RemoveAll(int val)
	{
		Node* temp = head_->next_;
		Node* pre = head_;
		while (temp != nullptr)
		{
			if (temp->data_ == val)
			{
				pre->next_ = temp->next_;
				delete temp;
				temp = pre->next_;
			}
			else
			{
				temp = temp->next_;
				pre = pre->next_;
			}
		}

	}
	//问题1：反置
	void ReverseLink()
	//对后面的元素全部重新头插法一次
	{
		Node* p = head_->next_;
		head_->next_ = nullptr;
		while (p != nullptr)
		{
			Node* q = p->next_;
			p->next_ = head_->next_;
			head_->next_ = p;
			p = q;
		}
	}
	//问题2：单链表倒数第k个节点
	int GetLastKNode(int k)
	{
		Node* pre = head_;
		Node* p = pre;

		if (k < 1)
		{
			return INT16_MAX;
		}//边界值判定

		for (int i = 0; i < k; i++)
		{
			p = p->next_;
			if (p->next_ == nullptr)
			{
				return INT16_MAX;
			}
		}
		while (p != nullptr)
		{
			p = p->next_;
			pre = pre->next_;
		}
		return pre->data_;
	} 
	//问题3：合并两个有序的单链表
	//last追随，p，q归并
	void MergeLink(Clink& L)
	{
		Node* p = this->head_->next_;
		Node* q = L.head_->next_;
		Node* last = this->head_;
		while (p != nullptr && q != nullptr)
		{
			if (p->data_ <= q->data_)
			{
				last->next_ = p;
				p = p->next_;
				last = last->next_;
			}
			else
			{
				last->next_ = q;
				q = q->next_;
				last = last->next_;
			}
		}
		last->next_ = (p != nullptr) ? p : q;
		L.head_->next_ = nullptr;
	}
	//问题4：单链表是否存在环，环的起点是哪里
	//快慢指针
	//方法一：得知一圈节点数，再次用快慢指针让快指针先走一圈节点的数量然后两者同时向前，最终会在起点处相遇，此时正好多一圈
	//方法二：快指针多走的是一圈，快指针走的是慢指针的两倍，所以多走的就等于慢指针走的，用一圈减去相遇点，剩余的点和从起点到起始点的步数是一样的
	//		  所以让慢指针重新走，快指针继续一个一个走，相遇点就是环的起始点
	bool CircleIsExist(int& val)
	{
		Node* fast = this->head_;
		Node* slow = this->head_;
		int num = 0;
		while (fast != nullptr && fast->next_ != nullptr)
		{
			slow = slow->next_;
			fast = fast->next_->next_;
			if (slow == fast)
			{
				slow = this->head_;
				while (slow != fast)
				{
					slow = slow->next_;
					fast = fast->next_;
				}
				val = fast->data_; 
				return true;
			}
		}
		return false;
	}
	bool Find1(int val)
	{
		Node* temp = head_->next_;
		while (temp != nullptr)
		{
			if (temp->data_ == val)
			{
				return true;
			}
			else
			{
				temp = temp->next_;
			}
		}
		return false;
	}
	Node* Find2(int val)
	{
		Node* temp = head_->next_;
		while (temp != nullptr)
		{
			if (temp->data_ == val)
			{
				return temp;
			}
		}
		return nullptr; 
	}
	void Show()
	{
		Node* temp = head_->next_;
		while (temp != nullptr)//用当前节点来判断不容易漏掉节点
		{
			cout << temp->data_ << " ";
			temp = temp->next_;
		}
		cout << endl;
	}
private:
	Node* head_;
};
//问题五：判断两个单链表是否相交(快慢指针)
bool IsLinkHasMerge(Node*head1,Node* head2,int& val)
{
	int cnt1=0;
	int cnt2=0;
	Node* p = head1->next_;
	Node* q = head2->next_;
	while (p != nullptr)
	{
		p = p->next_;
		cnt1++;
	}
	while (q != nullptr)
	{
		q = q->next_;
		cnt2++;
	}
	p = head1;
	q = head2;
	if (cnt1 >= cnt2)
	{
		int offset = cnt1 - cnt2;
		for (int i = 0; i < offset; i++)
		{
			p = p->next_;
		}
	}
	else
	{
		int offset = cnt2 - cnt1;
		for (int i = 0; i < offset; i++)
		{
			q = q->next_;
		}
	}
	while (p != nullptr && q != nullptr)
	{
		p = p->next_;
		q = q->next_;
		if (p == q)
		{
			val = q->data_;
			return true;
		}
	}
	return false;
}
#if 0
int main()
{
#if 0
	Clink link;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		link.InsertTail(i);
	}
	link.Show();
	for (int i = 0; i < 10; i++)
	{
		link.InsertHead(rand() % 100);
	}
	link.Show();
	link.Remove(5);
	link.Show();
	link.InsertTail(23);
	link.InsertTail(23);
	link.InsertTail(23);
	link.InsertTail(23);
	link.Show();
	link.RemoveAll(23);
	link.Show();
	link.ReverseLink();
	link.Show();
	cout << link.GetLastKNode(0);
#endif
#if 0
	int arr[] = { 25,37,52,78,88,98,98,108 };
	int brr[] = { 13,23,40,56,62,77,109 };
	Clink link1;
	Clink link2;
	for (int v : arr)
	{
		link1.InsertTail(v);
	}
	for (int v : brr)
	{
		link2.InsertTail(v);
	}
	link1.Show();
	link2.Show();
	link1.MergeLink(link2);
	link1.Show();
#endif
	Node head1;
	Node head2;
	Node n1, n2, n3, n4, n5, n6, n7;
	Node n8 ,n9, n10;
	head1.next_ = &n1;
	n1.next_ = &n2;
	n2.next_ = &n3;
	n3.next_ = &n4;
	n4.next_ = &n5;
	n5.next_ = &n6;
	n6.next_ = &n7;
	head2.next_ = &n8;
	n8.next_ = &n9;
	n9.next_ = &n10;
	n10.next_ = &n5;
	
	int val;
	cout << IsLinkHasMerge(&head1, &head2, val) << endl;;
	cout << val << endl;
	system("pause");
}
#endif