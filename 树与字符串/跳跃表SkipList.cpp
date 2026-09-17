#include<iostream>
using namespace std;
class SkipList
{
public:
	SkipList()
	{
		headnode_ = new HeadNode(1);
	}
	~SkipList()
	{
		HeadNode* current_head = headnode_;
		while (current_head != nullptr)
		{
			Node* node = current_head->next_;
			while (node != nullptr)
			{
				Node* temp = node->next_;
				delete node;
				node = temp;
			}
			HeadNode* next_head = static_cast<HeadNode*>(current_head->down_);
			delete current_head;
			current_head = next_head;
		}
	}
	int getLevel()const
	{
		int level = 1;
		while (rand() % 2 == 1)
		{
			level++;
		}
		return level;
	}
	bool find(int data)
	{
		Node* pre = headnode_;
		Node* cur = pre->next_;
		while (1)
		{
			if (cur != nullptr)
			{
				if (cur->data_ < data)
				{
					pre = cur;
					cur = cur->next_;
					continue;
				}
				else if (cur->data_ == data)
				{
					return true;
				}
				else 
				{
					if (pre->down_ == nullptr) return false;
					pre = pre->down_;
					cur = pre->next_; 
				}
			}
			if (pre->down_ == nullptr)
			{
				return false;
			}
			pre = pre->down_;
			cur = pre->next_;
		}
	}
	void add(int data)
	{
		if (find(data))
			return;
		//抛硬币实现加几层
		int level = getLevel();
		if (level > headnode_->level_)
		{
			level = headnode_->level_ + 1;
			HeadNode* hnode = new HeadNode(level);
			hnode->down_ = headnode_;
			headnode_ = hnode;
		}
		Node** nodeList = new Node * [level];
		for (int i = level - 1;i >= 0;i--)//nodeList[level-1]的down是nullptr
		//后面的每一个的down都是前一个节点的地址	
		{
			nodeList[i] = new Node(data);
			if (i < level - 1)
			{
				nodeList[i]->down_ = nodeList[i + 1];
			}
		}
		//求最高层的头节点指针
		HeadNode* head = headnode_;
		for (int i = head->level_;i > level;i--)
		{
			head = static_cast<HeadNode*>(head->down_);
		}
		//进行添加
		Node* pre = head;
		Node* cur = pre->next_;
		for (int i = 0;i < level;i++)
		{
			while (cur != nullptr && cur->data_ < data)
			{
				pre = cur;
				cur = cur->next_;
			}
			nodeList[i]->next_ = cur;
			pre->next_ = nodeList[i];
			pre = pre->down_;
			if (pre != nullptr)
			{
				cur = pre->next_;
			}
		}
		delete[] nodeList;
	}
	void show()const
	{
		Node* head = headnode_;
		for (int i = 0;i < headnode_->level_;i++)
		{
			Node* cur = head->next_;
			while (cur != nullptr)
			{
				cout << cur->data_ << " ";
				cur = cur->next_;
			}
			cout << endl;
			head = head->down_;
		}
	}
	void remove(int data)const
	{
		Node* pre = static_cast<Node*>(headnode_);
		Node* cur = pre->next_;
		while (pre!=nullptr)
		{
			if (cur != nullptr)
			{
				if (cur->data_ < data)
				{
					pre = cur;
					cur = cur->next_;
				}
				else if (cur->data_ == data)
				{
					pre->next_ = cur->next_;
					delete cur;
					pre = pre->down_;
					if (pre != nullptr)
					{
						cur = pre->next_;
					}
				}
				else
				{
					pre = pre->down_;
					if (pre != nullptr)
					{
						cur = pre->next_;
					}
				}
			}
			else
			{
				pre = pre->down_;
				if (pre != nullptr)
				{
					cur = pre->next_;
				}
			}
		}
	}
private:
	struct Node 
	{
		Node(int data=0) :data_(data), next_(nullptr), down_(nullptr) {};
		int data_;
		Node* next_;
		Node* down_;
	};
	struct HeadNode :public Node
	{
		HeadNode(int level) :level_(level){};
		int level_;
	};
private:
	HeadNode* headnode_;

};
#if 0
int main()
{
	SkipList sL;
	srand(time(0));
	for (int i = 0;i < 20;i++)
	{
		sL.add(rand() % 100);
	}
	sL.add(59);
	cout << sL.find(59) << endl;
	sL.remove(59);
	sL.show();
	system("pause");
	return 0;
}
#endif