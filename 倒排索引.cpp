/*
倒排索引
倒排索引常使用在搜索引擎中，是搜索引擎为文档内容建立索引，实现内容快速检索必不可少的数据结构
倒排索引是由单词的集合"词典"和倒排列表的集合"倒排文件"组成的
倒排索引的存储：内存索引（哈希索引）和B+树索引
应用：
搜索引擎启动之后，提供搜索服务之前就已经给全网搜索到的html网页页面内容建立了倒排索引结构
全文索引：
全文本匹配索引
利用索引进行全文搜索
正排索引结构：行：文档，列：单词，缺点必须去每一个文档找
倒排索引结构：行：单词，列：文档。
单词所在文档的信息：倒排项：docid(文档名字/标识):freqs(文档中该单词出现的次数):pos(文档里的第几个单词，单词在文档中的位置):line(单词在该文件的行数)
多个倒排项组成一个单词的倒排列表，多个倒排列表组成倒排文件
多个单词组成单词
步骤：
对用户输入的搜索句子进行分词
搜索
给搜索结果打分：求交集，判断交集文档的优先级，并展示
*/
#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE

#include <Windows.h>
#include <cstring>
#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
//倒排项
struct InvertTerm
{
	InvertTerm(string docid, int freqs, int location) :docid_(docid), freqs_(freqs)
	{
		locations_.emplace_back(location);
	}
	bool operator==(const InvertTerm& term)const
	{
		return docid_ == term.docid_;
	}
	bool operator<(const InvertTerm& term)const
	{
		return docid_ < term.docid_;
	}
	string docid_;			//单词所在文档
	int freqs_;				//单词出现次数
	list<int>locations_;	//单词出现位置
};
//倒排列表
class InvertList
{
public:
	void addTerm(string docid,int location)
	{
		for (auto& term : termList_)
		{
			if (term.docid_ == docid)
			{
				term.freqs_++;
				term.locations_.push_back(location);
				return;
			}
		}
		termList_.emplace_back(docid, 1, location);
	}
	const list<InvertTerm>& getInvertList()const
	{
		return termList_;
	}
private:
	list<InvertTerm>termList_;
};
//倒排索引
class InvertIndex
{
public:
	//设置文档搜索的所有根路径
	void setSearch(string path)
	{
		cout << "searchFiles..."<<endl;
		GetAllFile(path.c_str());
		cout <<"finished!" << endl;
		cout << "create... loading..." << endl;
		createInvertIndex();
		cout << "finished" << endl;
	}
	//设置文档搜索的后缀过滤
	void setSuffix(string suffix)
	{
		suffix_ = suffix;
	}
	//设置文档查询接口
	void query(string phrase)
	{
		//先进行句子的分词操作
		vector<string>wordList;
		char* word = strtok(const_cast<char*>(phrase.c_str()), " ");
		while (word != nullptr)
		{
			word = trim(word);
			if (strlen(word) > 0)
			{
				wordList.emplace_back(word);
			}
			word = strtok(nullptr, " ");
		}
		if (wordList.empty())
			return;
		if (wordList.size() == 1)
		{
			auto it = invert_Map.find(wordList[0]);
			if (it == invert_Map.end())
			{
				cout << "404not found!" << endl;
				return;
			}
			for (auto& term : it->second.getInvertList())
			{
				cout << term.docid_ << " freqs:" << term.freqs_ << endl;
			}
		}
		else
		{
			//多个单词的查询进行合并处理
			//存所有倒排索引存在单词的倒排列表
			vector<InvertList>invertList;
			for (int i = 0;i < wordList.size();i++)
			{
				auto it = invert_Map.find(wordList[i]);
				if (it != invert_Map.end())
				{
					invertList.emplace_back(it->second);
				}
			}
			//找所有倒排列表的交集
			vector <InvertTerm>v1(invertList[0].getInvertList().begin(), invertList[0].getInvertList().end());
			vector<InvertTerm>share;
			for (int i = 1;i < invertList.size();i++)
			{
				vector <InvertTerm>v2(invertList[i].getInvertList().begin(), invertList[i].getInvertList().end());
				sort(v1.begin(), v1.end());
				sort(v2.begin(), v2.end());
				//set_intersection求集合交集时必须保证v1，v2是有序的
				set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(share));
				v1.swap(share);
				share.clear();
			}
			for (auto& term : v1)
			{
				cout << term.docid_ << " freqs_:" << term.freqs_ << endl;
				cout << "locations:";
				for (int pos : term.locations_)
				{
					cout << pos << " ";
				}
				cout << endl;
			}
		}
	}
	
private:
	//创建倒排索引结构
	void createInvertIndex()
	{
		for (string& filePath : fileList_)
		{
			cout << ".";
			FILE* pf = fopen(filePath.c_str(), "r");
			if (pf == nullptr)
			{
				cerr << filePath << " ......failed!" << endl;
				continue;
			}

			//按行读取文件内容，按照" "空格进行分词
			vector<string>wordList;
			int location = 0;
			const int LINE_SIZE = 2048;
			char line[LINE_SIZE] = { 0 };
			while (!feof(pf))
			{
				fgets(line, LINE_SIZE, pf);
				char* word = strtok(line, " ");
				while (word != nullptr)
				{
					word = trim(word);
					if (strlen(word) > 0)
					{
						wordList.emplace_back(word);
					}
					word = strtok(nullptr, " ");
				}
			}
			//开始给里面的单词创建或者修改倒排列表
			for (string& w : wordList)
			{
				location++;
				auto it = invert_Map.find(w);
				if (it == invert_Map.end())
				{
					InvertList list;
					list.addTerm(filePath, location);
					invert_Map.emplace(w,list);
				}
				else
				{
					it->second.addTerm(filePath, location);
				}
			}
			fclose(pf);
		}
	}
	//递归查找文件，找到符合要求的文件路径
	int GetAllFile(const char* Path)
	{
		char szFind[MAX_PATH];
		WIN32_FIND_DATA FindFileData;
		strcpy(szFind, Path);
		strcat(szFind, "\\*.*");
		HANDLE hFind = FindFirstFile(szFind, &FindFileData);
		if (INVALID_HANDLE_VALUE == hFind)
			return -1;

		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(
					FindFileData.cFileName, "..") != 0)
				{
					//发现子目录，递归之
					char szFile[MAX_PATH] = { 0 };
					strcpy(szFile, Path);
					strcat(szFile, "\\");
					strcat(szFile, FindFileData.cFileName);
					GetAllFile(szFile);
				}
			}
			else
			{
				//找到文件，处理之
				string fileName(FindFileData.cFileName);
				int pos = fileName.find(suffix_);
				if (pos != string::npos&&pos+suffix_.size()==fileName.size())
				{
					//std::cout << Path << "\\" << FindFileData.cFileName << std::endl;
					string filePath(Path);
					filePath.append("\\");
					filePath.append(fileName);
					fileList_.emplace_back(filePath);
				}
			}
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);

		return 0;
	}
	char* trim(char* word)
	{
		int i = 0;
		while (word[i] != '\0')
		{
			if (word[i] == ' ' || word[i] == '\t' || word[i] == '\n')
			{
				i++;
			}
			else
			{
				break;
			}
		}
		int j = i;
		while (word[j] != '\0')
		{
			if (word[j] == ' ' || word[j] == '\t' || word[j] == '\n')
			{
				break;
			}
			j++;
		}
		word[j] = '\0';
		return word + i;
	}
   
private:
	string suffix_;
	list<string>fileList_;
	unordered_map<string, InvertList>invert_Map;
};
#if 0
int main()
{
	InvertIndex index;
	index.setSuffix(".cpp");
	index.setSearch("D:\\project");
	for (;;)
	{
		char buf[128] = { 0 };
		cin.getline(buf, 128);
		index.query(buf);
	}
	cout << endl;
    system("pause");
    return 0;
}
#endif