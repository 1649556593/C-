//BF对i是全部回退的，造成了很多无效比较，比如ABCDEFG和ABCDH，当比较到E和H不一样之后全部回退，但是前面的四个字符没有相同的首位字符串
//所以元素都是一一对应的，那么回退之后的比较就一定是不相同的也就是无效的
//比如ABCABCABH和ABCABH，在比较D和H之后就不用回退到B，因为待查找字符串的首尾有相同字符串，那么就可以直接让j回退到C，i不动继续比较
#include<iostream>
#include<string>
using namespace std;
#if 0
int main()
{
	string s1 = "CEABADABABH";
	string s2 = "ABADABAB";
	const int sz1 = s1.size();	
	const int sz2 = s2.size();
	int* next = new int[sz2+1];
	next[0] = 0;//表示零个元素的最长公共前后缀的长度为0
	next[1] = 0;//表示一个元素的最长公共前后缀的长度为0；
	//求next数组
	//next数组表示有i个元素的时候的最长公共前后缀个数
	for (int i = 2;i <= sz2;i++)
	{
		//如果不同不一定要回到原点，比如ABADABAB，虽然B不等于D，但是AB仍然等于AB，也就是B和前面的三个字母中的某一部分再去和ABA适配
		//但是由于前面的ABA和后面的ABA又是一样的，所以就是要在ABAB中找公共前后缀，那么此时需要的就是next[3]的值，也就是把i放在了next[i-1]+1的位置上，也就是k
		//所以也可以说k就是新的i，套娃
		int k = next[i - 1];
		while (k > 0 && s2[k] != s2[i-1])
		{
			k = next[k];
		}
		if (s2[k] == s2[i-1])
		{
			next[i] = k+1;
		}
		else
		{
			next[i] = 0;
		}
	}
	for (int i=0;i<=sz2;i++)
	{
		cout << next[i] << " ";
	}
	cout << endl;
	//KMP算法实现 O(n)+O(m);

	int i = 0;
	int j = 0;
	while (i < sz1 && j < sz2)
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
		{
			if (j == 0)
			{
				i++;
			}
			else
			{
				j = next[j];
			}
		}
	}
	if (j == sz2)
		cout << 1<<" "<<i-j<< endl;
	else
		cout << 0 << endl;
	delete[] next;
	system("pause");
	return 0;
}
#endif