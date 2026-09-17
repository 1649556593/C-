#include<iostream>
using namespace std;
#include<vector>
#include <initializer_list>
#if 0
int find(int val, int left, int right, const vector<int>& v)
{
	if (left > right)
		return INT_MIN;
	int mid = (left + right) / 2;
	if (v[mid] == val)
	{
		return mid;
	}
	else if (v[mid] > val)
	{
		return find(val, left, mid-1, v);
	}
	else
	{
		return find(val,mid+1 , right, v);
	}
}
int main()
{
	vector<int>vec;
	for (int i = 0;i < 11;i++)
	{
		vec.push_back(i);
	}
	int val = 9;
	cout<<find(val, 0, vec.size() - 1,vec)<<endl;
	return 0;
}
#endif
#if 0
void my_qsort(vector<int>&v,int left,int right,int k)
{
	if (left >= right)
		return;
	int pivot = v[left];
	int num1 = left;
	int num2 = right;
	while (left < right)
	{
		while (v[right] >= pivot && left<right)
		{
			right--;
		}
		if (left < right)
		{
			v[left] = v[right];
		}
		while (v[left] < pivot&&left<right)
		{
			left++;
		}
		if (left < right)
		{
			v[right] = v[left];
		}
	}
	v[left] = pivot;
	if (left == k)
		return;
	else if (left > k)
	{
		my_qsort(v, num1, left - 1,k);
	}
	else
	{
		my_qsort(v, left + 1, num2,k);
	}
}
int main()
{
	vector<int>v;
	srand(time(0));
	for (int i = 0;i < 20;i++)
	{
		v.push_back(rand());
	}
	int k = 3;
	my_qsort(v, 0, v.size() - 1,3);
	for (auto it : v)
	{
		cout << it << " ";
	}
	cout << endl;
	for (int i = 0;i < 5;i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
	return 0;
}
#endif
#if 0
void my_mergesort(vector<int>& v,int left,int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	my_mergesort(v, left, mid);
	my_mergesort(v, mid + 1, right);
	vector<int>temp;
	int num1 = left;
	int num2 = mid + 1;
	while (num1 <= mid && num2 <= right)
	{
		if (v[num1] <= v[num2])
		{
			temp.push_back(v[num1++]);
		}
		else
		{
			temp.push_back(v[num2++]);
		}
	}
	while (num1 <= mid)
	{
		temp.push_back(v[num1++]);
	}
	while (num2 <= right)
	{
		temp.push_back(v[num2++]);
	}
	for (int i = left;i <= right;i++)
	{
		v[i] = temp[i-left];
	}
}
int main()
{
	vector<int>v;
	srand(time(0));
	for (int i = 0;i < 20;i++)
	{
		v.push_back(rand()%100);
	}
	my_mergesort(v,0,v.size()-1);
	for (auto it : v)
	{
		cout << it << " ";
	}
	cout << endl;
	return 0;
}
#endif
#if 0
struct ListNode
{
	ListNode(int val) :val_(val), next_(nullptr) {};
	int val_;
	ListNode* next_;
};
ListNode* init_link(initializer_list<int> list)
{
	ListNode* head = nullptr;
	ListNode* p = nullptr;
	for (int v : list)
	{
		if (head == nullptr)
		{
			head = new ListNode(v);
			p = head;
		}
		else
		{
			p->next_ = new ListNode(v);
			p = p->next_;
		}
	}
	return head;
}
ListNode* mergeTwoLink(ListNode* left, ListNode* right)
{
	ListNode* head=nullptr;
	ListNode* cur=nullptr;
	while (left != nullptr && right != nullptr)
	{
		if (left->val_ <= right->val_)
		{
			if (head == nullptr)
			{
				head = new ListNode(left->val_);
				cur = head;
				left = left->next_;
			}
			else
			{
				cur->next_ = new ListNode(left->val_);
				cur = cur->next_;
				left = left->next_;
			}
		}
		else
		{
			if (head == nullptr)
			{
				head = new ListNode(right->val_);
				cur = head;
				right = right->next_;
			}
			else
			{
				cur->next_ = new ListNode(right->val_);
				cur = cur->next_;
				right = right->next_;
			}
		}
	}
	while (left != nullptr)
	{
		cur->next_ = new ListNode(left->val_);
		cur = cur->next_;
		left = left->next_;
	}
	while (right != nullptr)
	{
		cur->next_ = new ListNode(right->val_);
		cur = cur->next_;
		right = right->next_;
	}
	return head;
}
ListNode* mergeLink(vector<ListNode*>&vlink,int i,int j)
{
	if (i > j)
	{
		return nullptr;
	}	
	if (i == j)
	{
		return vlink[i];
	}
	int mid = (i + j) / 2;
	ListNode* left = mergeLink(vlink, i, mid);
	ListNode* right = mergeLink(vlink, mid + 1, j);
	return mergeTwoLink(left, right);
}
int main()
{
	ListNode* p1 = init_link({ 1,3,5,7 });
	ListNode* p2 = init_link({ 1,2,4,6,8 });
	ListNode* p3 = init_link({ 4,9,10,11 });
	ListNode* p4 = init_link({ 5,15,19,20 });
	vector<ListNode*>vlink;
	vlink.push_back(p1);
	vlink.push_back(p2);
	vlink.push_back(p3);
	vlink.push_back(p4);
	ListNode* p = mergeLink(vlink,0,vlink.size()-1);
	ListNode* cur = p;
	while (cur != nullptr)
	{
		cout << cur->val_ << " ";
		cur = cur->next_;
	}
	cout << endl;
	return 0;
}
#endif
#if 0
//对数时间求两个有序数组的中位数
//两个数组找topk的方法：
/*
两个有序数组，如果能找到符合要求的i和j，使得arr[i-1]<brr[j]&&brr[j-1]<arr[i]
那么ij左边所有的元素就小于右边所有元素，左边的arr[i-1]和brr[j-1]就是最大的两个
取两者的最大值就是top(i+j)
如果找中位数就是找i+j+1使得等于中位数下标
*/
int findMidNumber(int arr[], int brr[], int begin, int end,int k,int n,int m)
{
	if (begin > end)
		return -1;
	int i = (begin + end) / 2;
	int j = k - i;
	int arr_left = (i > 0) ? arr[i - 1] : INT_MIN;
	int brr_left = (j > 0) ? brr[j - 1] : INT_MIN;
	int arr_right = (i < n) ? arr[i] : INT_MAX;
	int brr_right = (j < m) ? brr[j] : INT_MAX;
	if (arr_left <= brr_right && brr_left <= arr_right)
	{
		return i;
	}
	else
	{
		if (arr_left > brr_right)
		{
			return findMidNumber(arr, brr, begin, i - 1, k,n,m);
		}
		if (brr_left > arr_right)
		{
			return findMidNumber(arr, brr, i + 1, end, k,n,m);
		}
	}
}
int main()
{
	int arr[] = { 1,2,6,9,20,57,98 };
	int brr[] = { 0,4,5,7,18,29,64 };
	int n = sizeof(arr) / sizeof(int);
	int m = sizeof(brr) / sizeof(int);
	int k = (m + n + 1) / 2;
	int i=findMidNumber(arr, brr, 0, n-1,k,n,m);
	int j = k - i;
	int arr_left = (i > 0) ? arr[i - 1] : INT_MIN;
	int arr_right = (i < n) ? arr[i] : INT_MAX;
	int brr_left = (j > 0) ? brr[j - 1] : INT_MIN;
	int brr_right = (j < m) ? brr[j] : INT_MAX;
	if ((m + n) % 2 == 1)
	{
		cout << max(arr_left, brr_left) << endl;
	}
	else
	{
		cout << (max(arr_left, brr_left) + min(arr_right, brr_right)) / 2.0 << endl;
	}
	system("pause");
	return 0;
}
#endif
