//字典树，前缀树，单词查找树
//哈希表可以快速查找但无法对单词进行排序功能并且没有前缀查找功能 
//要实现单词排序，快速检索，前缀搜索功能  
/*
1.根节点不包含字符，除根节点以外的每一个节点包含一个字符
2.从根节点到某一节点，路径上经过的字符连接起来为该节点对应的字符串
3.每个节点的所有子节点包含的字符都不相同

算法核心有较多公共前缀效率高，否则内存占用空间大
利用字符串的公共前后缀来减少查询时间，最大限度减少无用的字符串比较
时间复杂度为O(m),m是要查找的单词中包含字母的个数

*/
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<queue>
using namespace std;
class TrieTree
{
public:
	TrieTree()
	{
		root_ = new TrieNode('\0', 0);
	}
	~TrieTree()
	{
		queue<TrieNode*>que;
		que.push(root_);
		while (!que.empty())
		{
			TrieNode* cur = que.front();
			que.pop();
			for (auto it : cur->nodeMap_)
			{
				que.push(it.second);
			}
			delete cur;
		}
	}
	void add(const string word)
	{
		TrieNode* cur = root_;
		for (int i = 0;i < word.size();i++)
		{
			auto childIt = cur->nodeMap_.find(word[i]);
			if (childIt != cur->nodeMap_.end())
			{
				cur = childIt->second;
			}
			else
			{
				TrieNode* temp = new TrieNode(word[i], 0);
				cur->nodeMap_.emplace(word[i], temp);
				cur = temp;
			}
		}
		cur->freqs_++;
	}
	int query(const string word)
	{
		TrieNode* cur = root_;
		for (int i=0;i < word.size();i++)
		{
			auto childIt = cur->nodeMap_.find(word[i]);
			if (childIt != cur->nodeMap_.end())
			{
				cur = childIt->second;
			}
			else
			{
				return 0;
			}
		}
		return cur->freqs_;
	}
	void preOrder()
	{
		string word;
		vector<string>wordList;
		preOrder(root_, word, wordList);
		for (auto word : wordList)
		{
			cout << word<<endl;
		}
	}
	vector<string>queryPrefix(const string& prefix)
	{
		TrieNode* cur = root_;
		vector<string>wordList;
		string word = prefix;
		for (int i = 0;i < prefix.size();i++)
		{
			auto childIt = cur->nodeMap_.find(prefix[i]);
			if (childIt == cur->nodeMap_.end())
			{
				throw"no such word";
			}
			else
			{
				cur = childIt->second;
			}
		}

		if (cur->freqs_ > 0)
		{
			wordList.emplace_back(word);
		}
		for (auto pair : cur->nodeMap_)
		{
			if(word==prefix)
				preOrder(pair.second, word, wordList);
			else
				preOrder(pair.second, word + pair.first, wordList);
		}

		return wordList;
	}
	void remove(const string word)
	{
		TrieNode* cur = root_;
		TrieNode* del = root_;
		char delch = word[0];
		for (int i = 0;i < word.size();i++)
		{
			auto it = cur->nodeMap_.find(word[i]);
			if (it == cur->nodeMap_.end())
			{
				throw"404not found!";
			}
			if (cur ->freqs_>0||cur->nodeMap_.size()>1)//表示有子字符串的或者是分支节点的不可以删除
 			{
				del = cur;//del是待删除节点的父节点
				delch = word[i];//delch是待删除节点的字符
			}
			cur = it->second;
		}
		if (cur->nodeMap_.empty())
		{
			TrieNode* child = del->nodeMap_[delch];
			del->nodeMap_.erase(delch);
			while (!child->nodeMap_.empty())
			{
				auto it = child->nodeMap_.begin();
				delete child;
				child = it->second;
			}
			delete child;
		}
		else
		{
			cur->freqs_ = 0;
		}
	}
private:
	struct TrieNode
	{
		TrieNode(char ch, int freqs) :ch_(ch), freqs_(freqs) {};
		char ch_;
		int freqs_;
		//存储孩子字符数据和结点指针的关系
		map<char, TrieNode*> nodeMap_;
	};
	TrieNode* root_;

private:
	void preOrder(TrieNode* node,string word,vector<string>&wordList)
	{
		if (node != root_)
		{
			word.push_back(node->ch_);
			if (node->freqs_ > 0)
			{
				wordList.emplace_back(word);
			}
		}
		for (auto pair : node->nodeMap_)
		{
			preOrder(pair.second, word, wordList);
		}
	}
	void preOrder1(TrieNode* node, string word, vector<string>& wordList)
	{
		if (node->freqs_ > 0)
		{
			wordList.emplace_back(word);
		}
		for (auto pair : node->nodeMap_)
		{
			preOrder(pair.second, word+pair.first, wordList);
		}
	}
};
#if 0
int main()
{
	TrieTree trie;
	trie.add("hello");
	trie.add("hello");
	trie.add("hellw");
	trie.add("hellw");
	trie.add("hellw");
	trie.add("hellw");
	cout<<trie.query("hello")<<endl;
	cout << trie.query("hellw") << endl;
	/*vector<string> vec = trie.queryPrefix("hell");
	for (auto it : vec)
	{
		cout << it << endl;
	}*/
	trie.remove("hello");
	cout << trie.query("hello")<<endl;
	system("pause");
	return 0;
}
#endif