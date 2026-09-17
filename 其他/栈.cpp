#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<stack>
using namespace std;
//栈特点：先进后出，后进先出
#if 0//顺序栈
class SeqStack
{
public:
	SeqStack(int size=10)
	{
		mpStack = new int[size];
		mtop = 0;
		mcap = size;
	}
	~SeqStack()
	{
		delete[] mpStack;
		mtop = 0;
	}
private:
	void extend(int size)
	{
		int* arr = new int[size];
		memcpy(arr, mpStack, sizeof(int) * mcap);
		delete[] mpStack;
		mpStack = arr;
		mcap = size;
	}
public:
	
	void push(int val)
	{
		if (mtop == mcap)
		{
			extend(2 * mcap);
		}
		mpStack[mtop] = val;
		mtop++;
	}
	void pop()
	{
		if (mtop == 0)
		{
			cout << "栈空" << endl;
			return;
		}
		mtop--;
	}
	void top()const
	{
		if (mtop == 0)
		{
			cout << "栈空" << endl;
			return;
		}
		cout << mpStack[mtop - 1] << endl;
	}
	int size() const { return mtop; }
	void empty()
	{
		mtop = 0;
	}
private:
	int* mpStack;
	int mtop;
	int mcap;
};


#endif

//链式栈
#if 0
class LinkStack
{
public:
	LinkStack()
	{
		head = new Node;
	}
	~LinkStack()
	{
		Node* p = head;
		while (p != nullptr)
		{
			head = head->next_;
			delete p;
			p = head;
		}
	}
	void push(int val)
	{
		Node* node = new Node(val);
		node->next_ = head->next_;
		head->next_ = node;
	}
	void top()const
	{
		if (head->next_ == nullptr)
			throw"栈空";
		cout << head->next_->data_ << endl;
	}
	void pop()
	{
		if (head->next_ == nullptr)
			throw"栈空";
		Node* p = head->next_;
		head->next_ = p->next_;
		delete p;
	}
	int size()
	{
		Node* p = head->next_;
		int num = 0;
		while(p != nullptr)
		{
			num++;
			p = p->next_;
		}
		return num;
	}
	bool empty()
	{
		return head->next_ == nullptr;
	}
private:
	struct Node
	{
		Node(int data=10):data_(data),next_(nullptr){}
		int data_;
		Node* next_;
	};
	Node* head;
};

int main()
{
	LinkStack s;
	for (int i = 0; i < 8; i++)
	{
		s.push(i);
	}
	s.pop();
	s.pop();
	s.pop();
	s.top();
	cout << s.size() << endl;
	cout << s.empty() << endl;
	cout << s.size() << endl;
	system("pause");
	return 0;
}
#endif
#if 0
//中缀表达式转后缀表达式
//1.遇到数字直接打印
//2.遇到字符如果优先级高于栈顶就入栈，低于或者等于栈顶就把栈顶打印输出再进入
//3.左括号没入栈时优先级最高，入栈之后优先级最低，遇到右括号先把栈内左括号前的字符清空
//为什么遇到优先级高的可以入栈，因为栈后进先出，后缀表达式里面没有括号和优先级，所以哪个运算符在前就谁优先，所以优先级高的先出栈
//为什么遇到优先级低的要把栈内比他优先级高的出栈，因为优先级低对应后缀表达式中运算符在后面，需要先把优先级高的出栈再放优先级低的
bool Priority(char ch, char topch)
{
	if (topch == '(')
		return true;
	else
	{
		if (ch == '*' || ch == '/')
		{
			if (topch == '+' || topch == '-')
				return true;
			else
				return false;
		}
		else
		{
			return false;
		}
		
	}
}
string MiddleToEndExpr(string expr)
{
	string result;
	stack<char> s;
	for (char ch : expr)
	{
		if (ch >= '0' && ch <= '9')
		{
			result += ch;
		}
		else
		{
			//两种特殊情况
			if (s.empty() || ch == '(')
			{
				s.push(ch);
			}
			else if (ch == ')')
			{
				char topch = s.top();
				while (topch != '(')
				{
					result += topch;
					s.pop();
					topch = s.top();
				}
				s.pop();
			}
			//非特殊情况
			else
			{
				//比较当前符号ch和栈顶符号top优先值
				char topch = s.top();
				while (!Priority(ch, topch))
				{
					result += topch;
					s.pop();
					if (s.empty())//注意判断栈是否为空
					{
						break;
					}
					else
					{
						topch = s.top();
					}
				}
				s.push(ch);
			}
		}
	}
	//最终弹出栈内所有符号
	while(!s.empty())
	{
		char topch = s.top();
		result += s.top();
		s.pop();
	}
	return result;
}
int main()
{
	string expr = "9*(3+6)/3+9-7";
	cout << MiddleToEndExpr(expr) << endl;
	system("pause");
	return 0;
}
#endif