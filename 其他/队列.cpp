#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;
//队列先进后出，由于数组是在后面加数据，所以后进的在后面，先进的在数组的前面
//因此队头指向数组的起始，队尾随着插入数据向后移动
//对于环形队列，rear==first的时候可能是队列为空也可能是队列满了，
//所以改变了队列满的判断条件,始终留下一个空位作为队列满的判断条件
//if((rear+1)%cap==first)队列满了
#if 0
class Queue
{
public:
	Queue(int size=10):front_(0),rear_(0),mcap(size)
	{
		marr = new int[size];
	}
	~Queue()
	{
		delete[] marr;
		marr = nullptr;
	}
	bool empty()const
	{
		return rear_ == front_;
	}
	//注意：由于循环队列的队列的队头不一定对应的下标零，如果单纯的用memcpy，复制完之后
	//front和rear的位置并没有发生变化，因此仍是队满，扩容无效
	void expend(int size)
	{
		int* temp = new int[size];
		int j = 0;
		for (int i = front_; i != rear_; i = (i + 1) % mcap)
		{
			temp[j++] = marr[i];
		}
		front_ = 0;
		rear_ = size_;
		mcap = size;
		delete[] marr;
		marr = temp;
	}
	void push(int val)
	{
		if ((rear_+1)%mcap==front_)
		{
			expend(2 * mcap);
		}
		marr[rear_] = val;
		rear_ = (rear_ + 1) % mcap;
		size_++;
	}
	void pop()
	{
		if (front_ == rear_)
		{
			throw "queue is empty";
			return;
		}
		front_ = (front_ + 1) % mcap;
		size_--;
	}
	int front()const
	{
		if (front_ == rear_)
		{
			throw "queue is empty";
		}
		return marr[front_];
	}
	int back()const
	{
		if (front_ == rear_)
		{
			throw "queue is empty";
		}
		return marr[(rear_ - 1 + mcap) % mcap];
	}
	int size1()const
	{
		return size_;
	}
	int size2()const
	{
		int size2 = 0;
		for (int i = front_; i != rear_; i = (i + 1) % mcap)
			size2++;
		return size2;
	}
	void Show()
	{
		int num1 = front_;
		int num2 = rear_;
		while (num1 != num2)
		{
			cout << marr[num1] << " ";
			num1 = (num1 + 1) % mcap;
		}
		cout << endl;
	}
private:
	int *marr;
	int front_;
	int rear_;
	int mcap;
	int size_;
};
int main()
{
	Queue q;
	for (int i = 0; i < 15; i++)
	{
		q.push(i);
	}
	q.Show();
	q.pop();
	q.Show();
	q.push(100);
	q.push(200);
	q.push(300);
	q.Show();
	cout << q.front() << endl;
	cout << q.back() << endl;
	cout << q.size1() << endl;
	cout << q.size2() << endl;
	system("pause");
	return 0;
}
#endif
#if 0
//链式栈
//不涉及扩容，但内存使用增加
//采用双向循环链表，双向的好处是head->pre就是尾节点，方便找
class LinkQueue
{
public:
	LinkQueue()
	{
		head = new Node();
		tail = head;
		head->next_ = head;
		head->pre_ = head;
	}
	~LinkQueue()
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
	void push(int val)
	{
		Node* node = new Node(val);
		node->next_ = head;
		node->pre_ = tail;
		tail->next_ = node;
		head->pre_ = node;
		tail = node;
	}
	void pop()
	{
		Node* p = head->next_;
		if (p == head)
		{
			throw "LinkQueue is empty!";
		}
		head->next_ = p->next_;
		p->next_->pre_ = head;
		if (p == tail)
		{
			tail = head;
		}
		delete p;
	}
	int back()const
	{
		Node* p = head->next_;
		if (p == head)
		{
			throw "LinkQueue is empty!";
		}
		return tail->data_;
	}
	int front()const
	{
		Node* p = head->next_;
		if (p == head)
		{
			throw "LinkQueue is empty!";
		}
		return head->next_->data_;
	}
	bool empty()
	{
		if (head == tail)
			return false;
		return true;
	}
	void Show()const
	{
		Node* p = head->next_;
		while (p != head)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}
	int size()
	{
		Node* p = head->next_;
		int num = 0;
		while (p != head)
		{
			num++;
			p = p->next_;
		}
		return num;
	}
private:
	struct Node
	{
		Node(int data=0):data_(data),pre_(nullptr),next_(nullptr){}
		int data_;
		Node* pre_;
		Node* next_;
	};
	Node* head;
	Node* tail;
};
int main()
{
	LinkQueue q;
	for (int i = 0; i < 15; i++)
	{
		q.push(i);
	}
	q.Show();
	q.pop();
	q.Show();
	q.push(100);
	q.push(200);
	q.push(300);
	q.Show();
	cout << q.front() << endl;
	cout << q.back() << endl;
	cout << q.size() << endl;
	system("pause");
	return 0;
}
#endif