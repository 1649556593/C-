#include<iostream>
using namespace std;
#include<cmath>
#include<stack>
template<typename T>
class AVLtree
{
public:
	AVLtree() :root_(nullptr) {}
	~AVLtree()
	{
		if (root_ == nullptr)return;
		stack<Node*>s;
		s.push(root_);
		while (!s.empty())
		{
			Node* node = s.top();
			s.pop();
			if (node->left_ != nullptr)
				s.push(node->left_);
			if (node->right_ != nullptr)
				s.push(node->right_);
			delete node;
		}
	}
	void insert(const T val)
	{
		root_=insert(root_, val);
	}
	void remove(const T val)
	{
		root_ = remove(root_, val);
	}
private:
	struct Node
	{
		Node(T data = T())
			:data_(data)
			, left_(nullptr)
			, right_(nullptr)
			, height_(1)
		{ }
		T data_;
		Node* left_;
		Node* right_;
		int height_;
	};
	int height(Node* node)
	{
		return node == nullptr ? 0 : node->height_;
	}
	Node* root_;
	Node* rightRotate(Node* node)
	{
		Node* child = node->left_;
		node->left_ = child->right_;
		child->right_ = node;
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1 ;
		return child;
		//因为实际上我旋转了node和child并没有更改左右子树部分的结构，其它部分节点的高度只依赖于自己的结构，
		//因为他们就是底层，结构没有改变高度就一定没有改变，也就是只有node和child的高度改变了，更新的时候
		//只需要去找他们左右子树的高度最大值加1即可
	}
	Node* leftRotate(Node* node)
	{
		Node* child = node->right_;
		node->right_ = child->left_;
		child->left_ = node;
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		child->height_ = max(height(child->left_), height(child->right_)) + 1;
		return child;
	}
	Node* leftBalance(Node* node)
	{
		node->left_=leftRotate(node->left_);
		return rightRotate(node);
	}
	Node* rightBalance(Node* node)
	{
		node->right_ = rightRotate(node->left_);
		return leftRotate(node);
	}
	Node* insert(Node* node, const T& val)
	{
		//递归找到需要插入的位置然后进行局部的插入，局部的调整，其子树部分高度不会改变，
		//然后在回溯的过程中不断对祖先进行调整和高度更新
		if (node == nullptr)
		{
			return new Node(val);
		}
		if (node->data_ > val)
		{
			//递归部分
			node->left_ = insert(node->left_, val);
			//回溯部分
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) >= height(node->left_->right_))
				{
					node = rightRotate(node);
				}
				else
				{
					node = leftBalance(node);
				}
			}
		}
		else if (node->data_ < val)
		{
			node->right_ = insert(node->right_, val);
			if (height(node->right_) - height(node->left_) > 1)
			{
				if (height(node->right_->right_) >= height(node->right_->left_))
				{
					node = leftRotate(node);
				}
				else
				{
					node = rightBalance(node);
				}
			}
		}

		//因为子树中增加了新的节点，回溯过程中可能部分祖先节点不需要调整，但是高度也应该更新
		//所以在递归回溯时应该检测更新节点高度
		node->height_ = max(height(node->left_), height(node->right_)) + 1; 

		return node;
	}
	Node* remove(Node* node, const T val)
	{
		if (node == nullptr)
			return nullptr;
		if (node->data_ > val)
		{
			node->left_ = remove(node->left_, val);
			if (height(node->right_) - height(node->left_)>1)
			{
				if (height(node->right_->right_) >= height(node->right_->left_))
				{
					node = leftRotate(node);
				}
				else
				{
					node = rightBalance(node);
				}
			}
		}
		else if (node->data_ < val)
		{
			node->right_ = remove(node->right_, val);
			if (height(node->left_) - height(node->right_) > 1)
			{
				if (height(node->left_->left_) >= height(node->left_->right_))
				{
					node = rightRotate(node);
				}
				else
				{
					node = leftBalance(node);
				}
			}
		}
		else
		{
			if (node->left_ != nullptr && node->right_ != nullptr)
			{
				//为了避免删除前驱或者后继节点造成节点失衡，谁高删除谁
				if (height(node->left_) >= height(node->right_))
				{
					Node* pre = node->left_;
					while (pre->right_ != nullptr)
					{
						pre = pre->right_;
					}
					node->data_ = pre->data_;
					node->left_ = remove(node->left_, pre->data_);
				}
				else
				{
					Node* pre = node->right_;
					while (pre->left_ != nullptr)
					{
						pre = pre->left_;
					}
					node->data_ = pre->data_;
					node->left_ = remove(node->right_, pre->data_);
				}
			}
			else
			{
				if (node->left_ != nullptr)
				{
					Node* left = node->left_;
					delete node;
					return left;
				}
				else
				{
					Node* right = node->right_;
					delete node;
					return right;
				}
			}
		}
		node->height_ = max(height(node->left_), height(node->right_)) + 1;
		return node;
	}
};
#if 0
int main()
{
	AVLtree<int> avl;
	for (int i = 1;i <= 10;i++)
	{
		avl.insert(i);
	}
	avl.remove(1);
	system("pause");
	return 0;
}
#endif