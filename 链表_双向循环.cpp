#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
struct Node
{
	Node(int data = 0)
		:data_(data)
		, next_(nullptr)
		, pre_(nullptr)
	{ }
	int data_;
	Node* next_;
	Node* pre_;
};
class DoubleCircleLink
{
public:
	DoubleCircleLink()
	{
		head = new Node;
		head->pre_ = head;
		head->next_ = head;
		tail = head;
	}
	~DoubleCircleLink()
	{
		Node* p = head->next_;
		while (p != head)
		{
			Node* temp = p->next_;
			delete p;
			p = temp;
		}
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	void InsertHead(int val)
	{
		Node* node = new Node(val);
		node->pre_ = head;
		node->next_ = head->next_;
		head->next_ = node;
		node->next_->pre_ = node;
		if (head == tail)
			tail = node;
	}
	void InsertTail(int val)
	{
		Node* node = new Node(val);
		node->pre_ = tail;
		node->next_ = tail->next_;
		tail->next_ = node;
		node->next_->pre_ = node;
		tail = node;
	}
	bool Remove(int val)
	{
		Node* p = head->next_;
		while (p != head)
		{
			if (p->data_ == val)
			{
				p->pre_->next_ = p->next_;
				p->next_->pre_ = p->pre_;
				if (p == tail)
					tail = p->pre_;
				delete p;
				return true;
			}
		}
		return false;
	}
	void Show()
	{
		Node* p = head->next_;
		while (p != head)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}
private:
	Node* head;
	Node* tail;
};
#if 0
int main()
{
	DoubleCircleLink dlink;
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