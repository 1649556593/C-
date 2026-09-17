#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<stack>
#include<queue>
//两个栈实现一个队列
//s1用来push，当需要pop或者top时看s2是不是空的
//如果是空的就把s1出栈并压入s2，这样后进s1的先进s2，在栈底，在s2中实现后进后出
//这样做会使一次的时间复杂度为O(n)而其他的都是O（1）,均摊时间复杂度达到O(1)
//(1*n+(n-1)*1)/n=1;
class MyQueue
{
public:
    MyQueue()
    {

    }

    void push(int x)
    {
        s1.push(x);
    }

    int pop()
    {
        if (s2.empty())
        {
            while (!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int temp = s2.top();
        s2.pop();
        return temp;
    }

    int peek()
    {
        if (s2.empty())
        {
            while (!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }

    bool empty()
    {
        if (s1.empty() && s2.empty())
            return true;
        return false;
    }
private:
    stack<int> s1;
    stack<int> s2;
};
//用队列实现栈
//找一个空队列入队，这样入对的元素在队头就可以先出，符合栈的要求
//然后把另一个队列的元素（已经按栈的要求排列好的）全部出队再入队进入前一个队列
//这样就又是一个符合栈要求的队列依次往复
class MyStack
{
public:
    MyStack()
    {

    }

    void push(int x)
    {
        if (q1.empty())
        {
            q1.push(x);
            while (!q2.empty())
            {
                q1.push(q2.front());
                q2.pop();
            }
        }
        else
        {
            q2.push(x);
            while (!q1.empty())
            {
                q2.push(q1.front());
                q1.pop();
            }
        }
    }

    int pop()
    {
        if (!q1.empty())
        {
            int temp = q1.front();
            q1.pop();
            return temp;
        }
        else
        {
            int temp = q2.front();
            q2.pop();
            return temp;
        }
    }

    int top()
    {
        if (!q1.empty())
        {
            return q1.front();
        }
        else
        {
            return q2.front();
        }
    }

    bool empty()
    {
        return q1.empty() && q2.empty();
    }
private:
    queue<int> q1;
    queue<int> q2;
};