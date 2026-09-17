#define _CRT_SECURE_NO_WARNINGS
#include<queue>
/*
（1） 内置基础类型
直接分配内存，不会初始化，值为随机垃圾值
int* p1 = new int;

加()后会执行值初始化，内置类型会被初始化为0
int* p2 = new int();

（2） 自定义类类型
class MyClass 
{
public:
	无参默认构造函数
	MyClass() { std::cout << "默认构造" << std::endl; }
};

会调用默认构造函数，创建对象并初始化
MyClass* p1 = new MyClass;
MyClass* p2 = new MyClass();
// 两种写法等价，都会触发默认构造，加()是显式声明调用无参构造
（3） 带参数的构造函数
必须加()并传入参数，否则编译器会报错：

MyClass* p = new MyClass(100, "test");  正确，调用带参构造
MyClass* p = new MyClass 100;  语法错误
（4） 动态数组
new数组时不能加()传参，但可以用{}初始化列表（C++11及以后）：

分配10个int的数组，元素默认初始化为0
int* arr1 = new int[10]();
分配并显式初始化前3个元素，其余为0
int* arr2 = new int[10]{1,2,3};
*/
#include<iostream>
using namespace std;
#include<functional>
#include<stack>
#include<vector>
template<typename T,typename Comp=less<T>>
class BSTree
{
public:
	struct Node
	{
		Node(T data = T()) ://如果T是内置数据类型创建实例化对象0，false等，如果不是内置类型就默认构造创建实例化对象
			data_(data),
			left_(nullptr),
			right_(nullptr)
		{
		}
		T data_;
		Node* left_;
		Node* right_;
	};
	BSTree(Comp com=Comp()) :
		root_(nullptr) ,
		comp(com)
	{}
	~BSTree()
	{
		if (root_ != nullptr)
		{
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
	}
	Node* getRoot()
	{
		return root_;
	}
	//非递归实现插入删除和查询
	void insert(const T val)
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
			if (comp(val,cur->data_))
			{
				parent = cur;
				cur = cur->left_;
			}
			else if(comp(cur->data_, val))
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				return;
			}
		}
		if (comp(val , parent->data_))
		{
			parent->left_ = new Node(val);
		}
		else
		{
			parent->right_ = new Node(val);
		}
	}
	void erase(const T val)
	{
		if (root_ == nullptr)
			return ;
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (comp(val, cur->data_))
			{
				parent = cur;
				cur = cur->left_;
			}
			else if (comp(cur->data_, val))
			{
				parent = cur;
				cur = cur->right_;
			}
			else
			{
				break;
			}
		}
		if (cur == nullptr)
			return;
		//一共分为两种情况，有两个子节点的情况和不够两个子节点的情况
		if ((cur->left_ != nullptr) && (cur->right_ != nullptr))
		//先统一把有两个节点的情况转化为只有一个节点的情况
		//找前驱节点，在左子树一直向右找最大
		{
			parent = cur;
			Node* pre = cur->left_;
			while (pre->right_ != nullptr)
			{
				parent = pre;
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;
		}
		//如果左孩子为空，那么右孩子可能为空可能不为空，但处理方式是一样的
		//都是把右孩子的值接在原来cur的位置上
		//如果左孩子不为空，那右孩子一定为空，处理方式也是一样的，直接把左孩子放在原来cur的位置即可
		Node* child = cur->left_;
		if (child == nullptr)
		{
			child = cur->right_;
		}
		if (parent == nullptr)//注意如果删除的是根节点而且根节点不够两个孩子，那么parent就会一直为空
		{
			root_ = child;
		}
		else if (parent->left_ == cur)
		{
			parent->left_ = child;
		}
		else
		{
			parent->right_ = child;
		}
		delete cur;
	}
	bool query(const T val)
	{
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (comp(val, cur->data_))
			{
				cur = cur->left_;
			}
			else if (comp(cur->data_, val))
			{
				cur = cur->right_;
			}
			else
			{
				break;
			}
		}
		if (cur == nullptr)
			return false;
		return true;
	}
	//递归实现插入
	void insert2(const T val)
	{
		root_ = insert2(root_, val);
	}
	//递归实现查询
	bool query2(const T val)
	{
		return nullptr != query2(root_, val);
	}
	//递归实现删除
	void erase2(const T val)
	{
		root_ = erase2(root_, val);
	}
	//递归实现前中后序遍历
	void Preorder_traversal()
	{
		cout << "前序遍历" << endl;
		Preorder_traversal(root_);
		cout << endl;
	}
	void Inorder_traversal()
	{
		cout << "中序遍历" << endl;
		Inorder_traversal(root_);
		cout << endl;
	}
	void Postorder_traversal()
	{
		cout << "后序遍历" << endl;
		Postorder_traversal(root_);
		cout << endl;
	}
	//非递归实现前中后序遍历
	void Preorder()
	{
		cout << "非递归前序遍历: ";
		if (root_ == nullptr)
		{
			return;
		}
		stack<Node*>s;
		s.push(root_);
		while (!s.empty())
		{
			Node* top = s.top();
			s.pop();
			cout << top->data_ << " ";
			if (top->right_ != nullptr)
			{
				s.push(top->right_);
			}
			if (top->left_ != nullptr)
			{
				s.push(top->left_);
			}
		}
		cout << endl;
		//也是栈，跟递归本质上都是一样的
	}
	void Inorder()
	{
		cout << "非递归中序遍历：";
		if (root_ == nullptr)
			return;
		stack<Node*>s;
		Node* cur = root_;
		while (cur != nullptr)
		{
			s.push(cur);
			cur = cur->left_;
		}
		while (!s.empty())
		{
			Node* top = s.top();
			s.pop();
			cout << top->data_ << " ";
			cur = top->right_;
			while (cur != nullptr)
			{
				s.push(cur);
				cur = cur->left_;
			}
		}
		cout << endl; 
	}
	void Postorder()
	{
		cout << "非递归后序遍历：";
		//后序遍历本身是需要记录LR之后才能打印V，但是由于V提前出栈后才能找R因此会丢失掉V
		//所以采用两个栈来实现，把LRV转为VRL，也就类似于前序遍历
		if (root_ == nullptr)
			return;
		stack<Node*>s1;
		stack<Node*>s2;
		s1.push(root_);
		while (!s1.empty())
		{
			Node* top = s1.top();
			s2.push(top);
			s1.pop();

			if (top->left_ != nullptr)
			{
				s1.push(top->left_);
			}
			if (top->right_ != nullptr)
			{
				s1.push(top->right_);
			}
		}
		while (!s2.empty())
		{
			cout << s2.top()->data_ << " ";
			s2.pop();
		}
		cout << endl;
	}
	//队列实现层序遍历
	void LevelOrder_Traversal(Node* p)const
	{
		queue<Node*> que;
		que.push(p);
		while (!que.empty())
		{
			Node* temp = que.front();
			cout << temp->data_ << " ";
			if (temp->left_ != nullptr)
			{
				que.push(temp->left_);
			}
			if (temp->right_ != nullptr)
			{
				que.push(temp->right_);
			}
			que.pop();
		}
	}
	//用递归实现层序遍历
	int high()
	{
		return high(root_);
	}
	int number()
	{
		return  number(root_);
	}
	void Levelorder_traversal()
	{
		//i和node是同步的，控制层数到相应层数的时候再去打印，给定一个层数，随着层数减减，node也随之向下
		//比如要打印第二层就传一个1，刚开始不打印，随着node到下一层，i也-1变成0，从而打印
		int h = high();
		for (int i = 0; i < h; i++)
		{
			Levelorder_traversal(root_, i);
		}
		cout << endl;
	}
	Node* getroot_()const
	{
		return root_;
	}
	//求满足区间的元素值[i,j]
	void findValues(int i,int j)
	{
		vector<T>vec;
		findValues(root_, vec, i, j);
		for (auto i : vec)
		{
			cout << i << " ";
		}
		cout << endl;
	}
	//判断该树是不是合法的BST树
	bool IsBSTtree()
	{
		T prev;
		bool first = true;
		return checkBST(root_, prev, first);
		//中序遍历就是从小到大排序，所以用中序遍历比较后者是否大于前者
	}
	//判断子树问题
	bool IsChildTree(BSTree<T, Comp>& child)
	{
		if (child.root_ == nullptr)
		{
			return true;
		}
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == child.root_->data_)
			{
				break;
			}
			else if (comp(cur->data_, child.root_->data_))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
		if (cur == nullptr)
		{
			return false;
		}
		return IsChildTree(cur, child.root_);
	}
	//求最近公共祖先节点
	int GetLCA(int val1, int val2)
	{
		Node*cur= GetLCA(root_,val1, val2);
		if (cur == nullptr)
		{
			throw"NO LCA!";
		}
		else
		{
			return cur->data_;
		}
		//从根节点找，如果同时小于就去右子树，同时大于就去左子树
		//如果同时小于一个值大于另一个值那么说明是最小公共祖先节点
		//为什么一定最小，因为这个祖先的左右孩子都不可能成为这两个节点的公共祖先
		//假设左孩子会成为公共祖先，那么原来的祖先就一定大于这两个值，产生矛盾，另一侧同理
	}
	//BST树的镜像反转问题
	void mirror01()
	{
		mirror01(root_);
	}
	//BST树镜像对称问题(左右子树形状是否对称)
	bool mirror02()
	{
		return mirror02(root_->left_, root_->right_) ;
	}  
	//重建二叉树
	void rebuild(int pre[], int i, int j, int in[], int m, int n)
	{
		root_ = rebuild1(pre, i, j, in, m, n);
	}
	//判断平衡树
	bool isBalance1(Node* node)
	{
		if (node == nullptr)
			return true;
		if (!isBalance1(node->left_))
			return false;
		if (!isBalance1(node->right_))
			return false;
		int left = high(node->left_);
		int right = high(node->right_);
		return abs(left - right) <= 1;
	}
	bool isBalance2(Node* node)
	{
		bool flag = true;
		isBalance2(root_, flag);
		return flag;
	}
	//求中序倒数第k个节点(LVR)
	int getVal(int k)
	{
		int i = 0;
		Node* node = getVal(root_, k,i);
		if (node == nullptr)
		{
			string err = "no No.";
			err += k;
			throw err;
		}
		else
		{
			return node->data_;
		}
	}
private:
	Node* root_;
	Comp comp;
	void Preorder_traversal(const Node* p)const
	{
		if (p == nullptr)
			return;
		cout << p->data_ << " ";
		Preorder_traversal(p->left_);
		Preorder_traversal(p->right_);
	}
	void Inorder_traversal(const Node* p)const
	{
		if (p == nullptr)
			return;
		Inorder_traversal(p->left_);
		cout << p->data_ << " ";
		Inorder_traversal(p->right_);
	}
	void Postorder_traversal(const Node* p)const
	{
		if (p == nullptr)
			return;
		Postorder_traversal(p->left_);
		Postorder_traversal(p->right_);
		cout << p->data_ << " ";
	}
	int high(Node* p)
	{
		if (p == nullptr)
			return 0;
		int left = high(p->left_);
		int right = high(p->right_);
		return left > right ? left + 1:right + 1;
		//相当于后序遍历，每当左右节点都遍历完之后，找出左右子树的层数最大值然后加1返回
	}
	int number(Node* p)
	{
		if (p == nullptr)
			return 0;
		int left = number(p->left_);
		int right = number(p->right_);
		return left + right + 1;
		//求二叉树节点个数
	}
	void Levelorder_traversal(Node* node, int i)const
	{
		if (node == nullptr) 
			return;
		if (i == 0)
		{
			cout << node->data_ << " ";
			return;
		}
		Levelorder_traversal(node->left_, i - 1);
		Levelorder_traversal(node->right_, i - 1);
		//i相当于在计算层数，只有减到0的时候才说明到达了要打印的一层，没有到0就向下遍历
	}
	Node* insert2(Node* node,const T val)
	{
		//找到相应的位置之后返回该点指针，由于需要建立父节点与该节点的关系，所以在每次入栈的时候都写node->left_/right_=insert()，
		//这样当找到对应的之后，执行完当前函数返回之后，直接就可以建立父节点与新建节点的关系
		//建立关系后，直接返回当前节点的指针，继续保持原来已有的父子关系。
		if (node == nullptr)//找到之后直接先加进去然后再回溯
		{
			return new Node(val);
		}
		if (comp(val, node->data_))
		{
			node->left_ = insert2(node->left_, val);
			return node;
		}
		else if(comp(node->data_,val))
		{
			node->right_ = insert2(node->right_, val);
			return node;
		}
		else
		{
			return node;//重复的不添加
		}
	}
	Node* query2(Node* node, const T val)
	{
		if (node == nullptr)
			return nullptr;
		if (comp(val, node->data_))
		{
			return query2(node->left_,val);
		}
		else if (comp(node->data_, val))
		{
			return query2(node->right_, val);
		}
		else
		{
			return node;
		}
	}
	Node* erase2(Node* node, const T val)
	{
		if (node == nullptr)
			return nullptr;
		if (node->data_ == val)
		{
			if ((node->left_ != nullptr) && (node->right_ != nullptr))
			{
				Node* pre = node->left_;
				while (pre->right_ != nullptr)
				{
					pre = pre->right_;
				}
				node->data_ = pre->data_;
				node->left_ = erase2(node->left_,pre->data_);//由于递归，所以必须该返回什么返回什么，不能一步跳到前驱节点
			}
			else
			{
				if (node->left_ != nullptr)
				{
					Node* temp = node->left_;
					delete node;
					return temp;
				}
				else
				{
					Node* temp = node->right_;
					delete node;
					return temp;
				}
			}
		}
		else if (comp(node->data_, val))
		{
			node->right_ = erase2(node->right_, val);
		}
		else
		{
			node->left_ = erase2(node->left_, val);
		}
		return node;
	}
	void findValues(Node* node, vector<T>& vec, int i, int j)
	{
		if (node != nullptr)
		{
			if (node->data_ > i)
			{
				findValues(node->left_, vec, i, j);
			}
			if (node->data_ >= i && node->data_ <= j)
			{
				vec.push_back(node->data_);
			}
			if (node->data_ < j)
			{
				findValues(node->right_, vec, i, j);
			}
		}
	}
	bool checkBST(Node* node, T& prev, bool& first)
	{
		//如果为空说明走到头了
		if (node == nullptr)return true;
		//先判断左子树
		if (!checkBST(node->left_, prev, first))return false;
		//再判断根节点，first表示是否为第一个节点(最小的)，如果是第一个prev没法比较直接跳过
		if (!first && node->data_ <= prev)return false;
		prev = node->data_;
		first = false;
		//最后判断右子树
		return checkBST(node->right_, prev, first);
	}
	bool IsChildTree(Node* father, Node* child)
	{
		if (father == nullptr && child == nullptr)
			return true;
		if (father == nullptr)
			return false;
		if (child == nullptr)
			return true;
		if (father->data_ != child->data_)
			return false;
		return IsChildTree(father->left_, child->left_);
		return IsChildTree(father->right_, child->right_);
	}
	Node* GetLCA(Node* node, int val1, int val2)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (comp(node->data_, val1) && comp(node->data_, val2))
		{
			return GetLCA(node->right_, val1, val2);
		}
		else if (comp(val1, node->data_) && comp(val2, node->data_))
		{
			return GetLCA(node->left_, val1, val2);
		}
		else
		{
			return node;
		}
	}
	void mirror01(Node* node)
	{
		if (node == nullptr)
			return;
		Node* temp = node->left_;
		node->left_ = node->right_;
		node->right_ = temp;
		mirror01(node->left_);
		mirror01(node->right_);
	}
	bool mirror02(Node* node1, Node* node2)
	{
		if (node1 == nullptr && node2 == nullptr)
			return true;
		if (node1 == nullptr || node2 == nullptr)
			return false;
		if (node1->data_ != node2->data_)
			return false;
		return mirror02(node1->left_, node2->right_)&& mirror02(node1->right_, node2->left_);
	}
	Node* rebuild1(int pre[], int i, int j, int in[], int m, int n)
	{
		if (i > j || m > n)
		{
			return nullptr;
		}
		Node* node = new Node(pre[i]);
		for (int k = m;k <= n;k++)
		{
			if (pre[i] == in[k])
			{
				node->left_ = rebuild1(pre, i + 1, i + k - m, in, m, k - 1);
				node->right_ = rebuild1(pre, i + k - m + 1, j, in, k + 1, n);
				return node;
			}
		}
	}
	int isBalance2(Node* node,  bool& flag)
	{
		if (node == nullptr)
			return 0;
		int left = isBalance2(node->left_, flag);
		if (!flag)
			return 0;
		int right = isBalance2(node->right_, flag);
		if (!flag)
			return 0;
		if (abs(left - right) > 1)
			flag = false;
		return max(left, right)+1;
	}
	Node* getVal(Node* node, int k, int& i)
	{
		//求RVL的第k个节点
		if (node == nullptr)
			return nullptr;
		Node* temp = getVal(node->right_, k, i);
		if (temp != nullptr)
			return temp;
		i++;
		if (k == i)
			return node;
		return getVal(node->left_, k, i);
	}
};
#if 0
int main()
{
	BSTree<int>bst;
	int arr[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	for (int v : arr)
	{
		bst.insert(v);
	}
#if 0
	bst.erase(58);
	bst.Preorder_traversal();
	bst.Inorder_traversal();
	bst.Postorder_traversal();
	bst.LevelOrder_Traversal(bst.getroot_());
	cout << endl;
	bst.Levelorder_traversal();
	bst.insert2(99);
	cout << bst.query2(99) << endl;
	bst.Levelorder_traversal();
	bst.erase2(34);
	bst.erase2(62);
	bst.erase2(99);
	bst.Levelorder_traversal();
	bst.Preorder();
	bst.Inorder();
	bst.Postorder();
	bst.findValues(3,50);
	cout << bst.IsBSTtree() << endl;
	cout << bst.GetLCA(0, 78) << endl;
#endif
#if 0
	int pre[] = { 58,24,0,5,34,41,67,62,64,69,78 };
	int in[] = { 0,5,24,34,41,58,62,64,67,69,78 };
	bst.rebuild(pre, 0, 10, in, 0, 10);
	bst.Preorder();
#endif
#if 0
	cout << bst.isBalance1(bst.getRoot()) << endl;
	cout << bst.isBalance2(bst.getRoot()) << endl;
#endif
	bst.Inorder();
	cout << bst.getVal(3) << endl;
  	system("pause");
 	return 0;
}
#endif