#include<iostream>
#include<string>
#include<unordered_map>
#include<queue>
#include<functional>
using namespace std;
using uint = unsigned int;
class HuffmanTree
{
public:
	HuffmanTree() :root_(nullptr), 
		minheap([](Node* node1, Node* node2)->bool {return node1->weight_ > node2->weight_;}) {};
	~HuffmanTree()
	{
		queue<Node*>que;
		que.push(root_);
		while (!que.empty())
		{
			Node* temp = que.front();
			que.pop();
			if (temp->left_ != nullptr)
				que.push(temp->left_);
			if (temp->right_ != nullptr)
				que.push(temp->right_);
			delete temp;
		}
	}
	void create(string str)
	{
		//先统计字符的权值
		unordered_map<char, uint>dataMap;
		for (char ch : str)
		{
			dataMap[ch]++;
		}
		for (auto& pair : dataMap)
		{
			minheap.push(new Node(pair.first, pair.second));
		}
		while (minheap.size() > 1)
		{
			Node* n1 = minheap.top();
			minheap.pop();
			Node* n2 = minheap.top();
			minheap.pop();
			Node* parent = new Node('\0', n1->weight_ + n2->weight_);
			parent->left_ = n1;
			parent->right_ = n2;
			minheap.push(parent);
		}
		root_ = minheap.top();
	}
	void showHuffmanCode()
	{
		string code;
		showHuffmanCode(root_,code);
		for (auto& pair : code_Map)
		{
			cout << pair.first << " " << pair.second << endl;
		}
	}
	string encode(string str)
	{
		string encode_str;
		for (char ch : str)
		{
			encode_str.append(code_Map[ch]);
		}
		return encode_str;
	}
	string decode(string encode)
	{
		string decode_str;
		Node* cur = root_;
		for (char ch : encode)
		{
			if (ch == '0')
			{
				cur = cur->left_;
			}
			else
			{
				cur = cur->right_;
			}
			if (cur->left_ == nullptr && cur->right_ == nullptr)
			{
				decode_str += cur->data_;
				cur = root_;
			}
		}
		return decode_str;
	}

private:
	struct Node
	{
		bool operator>(Node* node)
		{
			return weight_ > node->weight_; 
		}
		Node(char data, uint weight) :data_(data), weight_(weight), left_(nullptr), right_(nullptr) {};
		char data_;
		uint weight_;
		Node* left_;
		Node* right_;
	};
	Node* root_;
	unordered_map<char, string>code_Map;
	using MinHeap = priority_queue < Node*, vector<Node*>, function<bool(Node*, Node*)>>;
	MinHeap minheap;
private:
	void showHuffmanCode(Node* root, string code)
	{
		if (root->left_ == nullptr && root->right_ == nullptr)
		{
			code_Map[root->data_] = code;
			return;
		}
		showHuffmanCode(root->left_, code + '0');
		showHuffmanCode(root->right_, code + '1');
	}
};
#if 0
int main()
{
	HuffmanTree ht;
	ht.create("sakjabcsklahsafgysabchjvxmvxvxncbvuygqwdgsjbcznmvhgdqcvnmzxbgdajkdbnzmsbcxzguuwq");
	ht.showHuffmanCode();
	cout << ht.encode("hdjkahuif") << endl;
	cout << ht.decode("10010011000011000111101001010011100001") << endl;
	system("pause");
	return 0;
}
#endif
//文件的压缩和解压缩
//读取文件所有内容按字节统计字节数全值生成哈夫曼树，产生哈夫曼编码，encode把文件按字节编码，编码后的内容按位存储存储到磁盘文件
//还要把原始文件字节数据以及权值存储到压缩文件中