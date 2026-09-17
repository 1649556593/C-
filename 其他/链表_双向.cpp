#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
struct Node
{
	Node(int data = 0) 
		: data_(data)
		, pre_(nullptr)
		, next_(nullptr)
	{}
	int data_;
	Node* pre_;
	Node* next_;
};

class DoubleLink
{
public:
	DoubleLink()
	{
		head_ = new Node;
	}
	~DoubleLink()
	{
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
	}
	void InsertTail(int val)
	{
		Node* node = new Node(val);
		Node* p = head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}
		p->next_ = node;
		node->pre_ = p;
	}
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->pre_ = head_;
		node->next_ = head_->next_;
		head_->next_ = node;
		if(node->next_!=nullptr)
		node->next_->pre_ = node;
	}
	void Show()
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}
	bool Remove(int val)
	{
		int Flag = 0;
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				Flag = 1;
				p->pre_->next_ = p->next_;
				if (p->next_ != nullptr)
				{
					p->next_->pre_ = p->pre_;
				}
				Node* next = p->next_;
				delete p;
				p = next;
			}
			p = p->next_;
		}
		if (Flag == 1)
			return true;
		return false;
	}
private:
	Node* head_;
};
#if 0
int main()
{
	DoubleLink dlink;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		dlink.InsertHead(rand() % 100);
	}
	dlink.Show();
	dlink.InsertTail(57);
	dlink.InsertHead(57);
	for (int i = 0; i < 5; i++)
	{
		dlink.InsertTail(rand() % 100);
	}
	dlink.Show();
	cout << dlink.Remove(57) << endl;
	dlink.Show();
	system("pause");
}

#endif