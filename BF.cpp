#include<iostream>
using namespace std;
//朴素算法
string str1 = "ABCDCABDEFG";
string str2 = "ABD";
int BF(string s1, string s2)
{
	int i = 0;
	int j = 0;
	while (i < s1.size() && j < s2.size())
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == s2.size())
	{
		return i - j;
	}
	else
	{
		return -1;
	}
}
#if 0
int main()
{
#if 0
	int sz1 = str1.size();
	int sz2 = str2.size();
	int FLAT = 0;
	for (int i = 0;i < sz1-sz2+1;i++)
	{
		if (str1[i] == str2[0])
		{
			int temp = i;
			int j = 0;
			while (temp<sz1&&j<sz2&&str1[temp]==str2[j])
			{
				temp++;
				j++;
			}
			if (j == sz2)
			{
				FLAT = 1;
				break;
			}
		}
	}
#endif
	int pos = BF(str1, str2);
	cout << pos << endl;
	system("pause");
	return 0;
}
#endif