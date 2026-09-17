#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#if 0
struct Node
{
	Node(int data=0):data_(data),next_(nullptr){}
	int data_;
	Node* next_;
};
//约瑟夫环问题
void Joseph(Node* head)
{
	head = new Node(1);
	int n = 0;
	int k = 0;
	int m = 0;
	cin >> n >> k >> m;
 
	Node* pre = head;
	Node* end = head;
	for (int i = 2; i <= n; i++)
	{
		Node* node = new Node(i);
		pre->next_ = node;
		pre = node;
		if (i == n)
		{
			node->next_ = head;
			end = node;
		}
	}
	Node* p = head;
	Node* q = end;
	for (int i = 1; i < k; i++)
	{
		p = p->next_;
		q = q->next_;
	}
	int num = 1;
	while (p->next_!=p)
	{
		if (num == m)
		{
			cout << p->data_ << endl;
			q->next_ = p->next_;
			delete p;
			p = q->next_;
			num = 1;
		}
		p = p->next_;
		q = q->next_;
		num++;
	}
	cout << p->data_ << endl;
	delete p;
}
int main()
{
	Node* head = nullptr;
	Joseph(head);
	system("pause");
	return 0;
}
#endif
#if  0
class CircleLink
{
public:
	CircleLink()
	{
		head_ = new Node();
		tail_ = head_;
		head_->next_ = head_;
	}
	~CircleLink()
	{
		//head需要作为结束的条件
		//从head->next开始删
#if 0
		Node* p = head_->next_;
		while (p != head_)
		{
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		delete head_;
#endif
		Node* p = head_;
		while (p != tail_)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
		delete(tail_);
	}
public:
	void InsertTail(int val)//尾插法时间复杂度为O(1)
	{
		Node* node = new Node(val);
		node->next_ = tail_->next_;
		tail_->next_ = node;
		tail_=node;
	}
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		//特殊！！！边界情况！！！
		if (head_ == tail_)
		{
			tail_ = node;
		}
	}
	bool Remove(int val)
	{
		//注意边界条件：删除节点是不是末尾节点,如果是tail指向的内存被释放了，会成野指针
		Node* p = head_;
		Node* q = head_->next_;
		while (q != head_)//注意不再是nullptr
		{
			if (q->data_ == val)
			{
				p->next_ = q->next_;
				if (q == tail_)
					tail_ = p;
				delete q;
				return true;
			}
			q = q->next_;
		}
		return false;
	}
	bool Find(int val)
	{
		Node* p = head_->next_;
		while (p != head_)//注意不再是nullptr
		{
			if (val == p->data_)
				return true;
			p = p->next_;
		}
		return false;
	}
	void Show()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}
private:
	struct Node
	{
		Node(int data = 0) :data_(data), next_(nullptr) {};
		int data_;
		Node* next_;
	};
	Node* head_;
	Node* tail_;
};
int main()
{
	CircleLink clink;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		clink.InsertHead(rand() % 100);
	}
	clink.Show();
	for (int i = 0; i < 10; i++)
	{
		clink.InsertTail(i+5);
	}
	clink.Show();
	cout << clink.Remove(9) << endl;
	cout << clink.Find(1999) << endl;
	system("pause");
}
#endif
