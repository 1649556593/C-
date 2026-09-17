#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int BinarySearch(int* arr, int sz,int val)
{
	int left = 0;
	int right = sz - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (arr[mid] == val)
		{
			return mid;
		}
		else if (arr[mid] > val)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return -1;
}
int BinarySearch2(int* arr, int left,int right,int val)
{
	int mid = (left + right) / 2;
	if (arr[mid] == val)
	{
		return mid;
	}
	else if (arr[mid] > val)
	{
		return BinarySearch2(arr, left, mid - 1, val);
	}
	else
	{
		return BinarySearch2(arr, mid + 1, right, val);
	}
}
int func(int n)
{
	if (n == 0||n == 1)
		return 1;
	return n * func(n - 1);
}
#if 0
int main()
{
	int arr[] = { 12,25,34,39,45,57,63,78,82,96,100 };
	cout<<BinarySearch(arr, 11, 100)<<endl;
	cout << BinarySearch2(arr, 0, 10, 100) << endl;
	cout << func(3) << endl;
	system("pause");
	return 0;
}
#endif