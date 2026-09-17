/*
* 操作                 | AVL          | 红黑树
* ---------------------|--------------|--------------
* 平衡树               | 是           | 否
* 增删查时间复杂度     | O(logn)      | O(logn)
* insert最多旋转次数   | 2            | 2
* remove最多旋转次数   | O(logn)      | 3
*/
/*
 * AVL 树核心旋转机制解析：
 * 1. 插入操作 (Insert)：
 *    原理：Insert 的旋转 = 高度复原器
 *    过程：局部修复 -> 全局免疫
 *    结果：最多 2 次旋转
 *    解释：旋转后子树高度完全恢复到插入前的状态，上层祖先节点不受影响，回溯可直接终止。
 *
 * 2. 删除操作 (Delete)：
 *    原理：Delete 的旋转 = 高度压缩器  *    过程：局部修复 -> 全局传导
 *    结果：最多 O(log n) 次旋转
 *    解释：旋转后子树高度永久降低 1 层，高度变化的效应会向上传导，可能导致祖先节点失衡，需持续回溯调整。
 */
 /*
 红黑树性质：
 1.每一个节点都是有颜色的，不是黑色就是红色
 2.所有叶子节点都是黑色的叶子节点是NULL节点，不存储实际的数据
 3.root必须是黑色的
 4.每个红色节点必须有两个黑色的子节点或者说每个叶子节点到根节点的所有路径上不能有连续的红色节点
 5.从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点
 */
 //在红黑树上节点的左右子树高度差最多不能超过短的两倍（全黑和红黑交替）
/*
空树 插入黑色节点
非空 插入红色节点 检查父节点颜色，如果父节点是黑色插入完成
	 如果是红色则开始做红黑树的插入调整
*/
#include<iostream>
#include<stack>
using namespace std;
template<typename T>
class RBtree
{
public:
	RBtree() :root_(nullptr) {};
	~RBtree()
	{
		if (root_ == nullptr)
			return;
		stack <Node*>s;
		s.push(root_);
		while (!s.empty())
		{
			Node* cur = s.top();
			s.pop();
			if (cur->left_ != nullptr)
				s.push(cur->left_);
			if (cur->right_ != nullptr)
				s.push(cur->right_);
			delete cur;
		}
	}
	void insert(const T& val)
	{
		if (root_ == nullptr)
		{
			root_ = new Node(val);
			return;
		}
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				parent = cur;
				cur = cur->left_;
			}
			else if(cur->data_<val)
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				return;
			}
		}
		Node* node = new Node(val,parent,nullptr,nullptr,RED);
		if (parent->data_ > val)
		{
			parent->left_ = node;
		}
		else
		{
			parent->right_ = node;
		}
		if (RED == color(parent))
		{
			fixAfterInsert(node);
		}
	}
	void remove(const T& val)
	{
		if (root_ == nullptr)
			return;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ > val)
			{
				cur = cur->left_;
			}
			else if (cur->data_ < val)
			{
				cur = cur->right_;
			}
			else
			{
				break;
			}
		}
		if (cur == nullptr)
			return;
		if (cur->left_ != nullptr && cur->right_ != nullptr)
		{
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;
		}
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}
		if (child != nullptr)
		{
			child->parent_ = cur->parent_;
			if (cur->parent_ == nullptr)
			{
				root_ = child;
			}
			else
			{
				if (cur == cur->parent_->left_)
				{
					cur->parent_->left_ = child;
				}
				else
				{
					cur->parent_->right_ = child;
				}
			}
			Color c = color(cur);
			if (c == BLACK)
			{
				fixAfterRemove(child);
			}
			delete cur;
		}
		else
		{
			if (cur->parent_ == nullptr)
			{
				delete cur;
				root_ = nullptr;
			}
			else
			{
				//删除的cur就是叶子节点
				Node* parent = cur->parent_;
				bool isLeft = (cur == parent->left_);
				if (color(cur) == BLACK)
				{
					fixAfterRemove(cur);
				}
				if (isLeft)
					parent->left_ = nullptr;
				else
					parent->right_ = nullptr;
				delete cur;
			}
		}
		if(root_!=nullptr)
			setColor(root_, BLACK);
	}
private:
	enum Color
	{
		BLACK,RED
	};
	struct Node
	{
		Node(T data = T(), Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, Color color = BLACK)
			:data_(data)
			, parent_(parent)
			, left_(left)
			, right_(right)
			, color_(color)
		{}

		T data_;
		Node* left_;
		Node* right_;
		Node* parent_;
		Color color_;
	};
	Color color(Node* node)
	{
		if (node == nullptr)
			return BLACK;
		else
			return node->color_;
	}
	void setColor(Node* node, Color color)
	{
		if(node!=nullptr)
		node->color_ = color;
	}
	Node* left(Node* node) { return node==nullptr?nullptr:node->left_; };
	Node* right(Node* node) { return node == nullptr ? nullptr : node->right_; };
	Node* parent(Node* node) { return node == nullptr ? nullptr : node->parent_; };
	void leftRotate(Node* node)
	{
		Node* child = node->right_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr)
		{
			root_ = child;
		}
		else
		{
			if (node->parent_->left_ == node)
			{
				node->parent_->left_ = child;
			}
			else
			{
				node->parent_->right_ = child;
			}
		}
		node->right_ = child->left_;
		if (node->right_ != nullptr)
		{
			node->right_->parent_ = node;
		}
		child->left_ = node;
		node->parent_ = child;
	}
	void rightRotate(Node* node)
	{
		Node* child = node->left_;
		child->parent_ = node->parent_;
		if (node->parent_ == nullptr)
		{
			root_ = child;
		}
		else
		{
			if (node->parent_->left_ == node)
			{
				node->parent_->left_ = child;
			}
			else
			{
				node->parent_->right_ = child;
			}
		}
		node->left_ = child->right_;
		if (node->left_ != nullptr)
			node->left_->parent_ = node;
		child->right_ = node;
		node->parent_ = child; 
	}
	void fixAfterInsert(Node* node)
	{
		while (color(parent(node)) == RED)
		{
			if (left(parent(parent(node))) == parent(node))
			{
				//插入的节点在左子树
				Node* uncle = right(parent(parent(node)));
				if (RED == color(uncle))
				{
					setColor(parent(node), BLACK);
					setColor(uncle, BLACK);
					setColor(parent(parent(node)), RED);
					node = parent(parent(node));
				}
				else
				{
					if (right(parent(node)) == node)
					{
						node = parent(node);
						leftRotate(node);
					}
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					rightRotate(parent(parent(node)));
					break;
				}
			}
			else
			{
				//插入的节点在右子树
				Node* uncle = left(parent(parent(node)));
				if (RED == color(uncle))
				{
					setColor(parent(node), BLACK);
					setColor(uncle, BLACK);
					setColor(parent(parent(node)), RED);
					node = parent(parent(node));
				}
				else
				{
					if (left(parent(node)) == node)
					{
						node = parent(node);
						rightRotate(node);
					}
					setColor(parent(node), BLACK);
					setColor(parent(parent(node)), RED);
					leftRotate(parent(parent(node)));
					break;
				}
			}
		}
		setColor(root_, BLACK);
	}
	void fixAfterRemove(Node* node)
	{
		while (color(node) == BLACK&&node!=root_)
		{
			if (left(parent(node)) == node)
			{
				//删除的黑色节点在左子树
				Node* brother = right(parent(node));
				//情况四
				if (color(brother) == RED)
				{
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					leftRotate(parent(node));
					brother = right(parent(node));
				}
				//情况三
				if (color(left(brother)) == BLACK
					&& color(right(brother)) == BLACK)
				{
					setColor(brother, RED);
					node = parent(node);
				}
				else
				{
					//情况二
					if (color(right(brother)) != RED)
					{
						setColor(brother, RED);
						setColor(left(brother), BLACK);
						rightRotate(brother);
						brother = right(parent(node));
					}
					//归结到情况一
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(right(brother), BLACK);
					leftRotate(parent(node));
					break;
				}
				
			}
			else
			{
				//删除的黑色节点在右子树
				Node* brother = left(parent(node));
				//情况四
				if (color(brother) == RED)
				{
					setColor(parent(node), RED);
					setColor(brother, BLACK);
					rightRotate(parent(node));
					brother = left(parent(node));

				}
				//情况三
				if (color(right(brother)) == BLACK
					&& color(left(brother)) == BLACK)
				{
					setColor(brother, RED);
					node = parent(node);
				}
				else
				{
					//情况二
					if (color(left(brother)) != RED)
					{
						setColor(brother, RED);
						setColor(right(brother), BLACK);
						leftRotate(brother);
						brother = left(parent(node));
					}
					//归结到情况一
					setColor(brother, color(parent(node)));
					setColor(parent(node), BLACK);
					setColor(left(brother), BLACK);
					rightRotate(parent(node));
					break;
				}
			}
		}
		setColor(node, BLACK);//如果补上来的node是红色的，那么直接变黑即可，如果不是红色的就会进入循环中
		//当跳出循环的时候，情况一情况二处理之后的node也是黑色，所以变黑没有影响，情况三？
		//情况四修改之后会直接并入情况一二三中
	}
	Node* root_;
};
#if 0
int main()
{
	RBtree<int>rb;
	for (int i = 1;i <= 10;i++)
	{
		rb.insert(i);
	}
	rb.remove(6);
	rb.remove(2);
	rb.remove(4);
	rb.remove(5);
	system("pause");
	return 0;
}
#endif