#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//快排分割，平均时间复杂度O(n),最坏时间复杂度O(n²)
int partation(int* arr, int left, int right)
{
	int index = (left + right) / 2;
	int temp = arr[index];
	arr[index] = arr[left];
	arr[left] = temp;
	int pivot = arr[left];
	while (left < right)
	{
		while (arr[right] > pivot && left < right)
		{
			right--;
		}
		arr[left] = arr[right];
		while (arr[left] <= pivot && left < right)
		{
			left++;
		}
		arr[right] = arr[left];
	}
	arr[left] = pivot;
	return left;
}
void SelectTopK(int arr[], int left, int right, int k)
{
	int pos = partation(arr, left, right);
	if (pos + 1 == k)
	{
		return;
	}
	else if (pos + 1 < k)
	{
		SelectTopK(arr, pos + 1, right,k);
	}
	else
	{
		SelectTopK(arr, left, pos - 1, k);
	}
}
#if 0
int main()
{
	int arr[] = { 64,45,52,80,66,68,0,2,18,75 };
	int size = sizeof(arr) / sizeof(int);
	int k = 3;
	SelectTopK(arr, 0, size - 1,k);
	for (int i = 0; i < 3; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
#endif