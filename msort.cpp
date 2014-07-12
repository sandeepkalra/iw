#include <iostream>
using namespace std;

#define MAX_SZ  20
int A[] = { 1, 23, 21, 0, 41, 313, 9, 12 };

void merge(int *array, int start, int mid, int end)
{
	int temp[MAX_SZ] = {};
	int left = start;
	int right = mid;
	int i = 0;
	while (left < mid && right < end)
	{
			if (array[left] < array[right])
				temp[i++] = array[left++];
			else
				temp[i++] = array[right++];
	
	}
	while(left<mid)
	{
		temp[i++] = array[left++];
	}
	while(right<end)
	{
		temp[i++] = array[right++];
	}
	
	for (int j = start,i=0; j < end; ++j,i++) array[j] = temp[i];
}

void mergesort(int *array, int start, int end/*not included*/)
{
	int sz = end - start;
	if (sz>1)
	{
		int split = (end-start) / 2;
		int mid = start + split;//////////////////TRICKY!!
		mergesort(array, start, mid);
		mergesort(array, mid, end);
		merge(array, start, mid, end);
	}
}

int main()
{
	int sz = sizeof(A) / sizeof(int);
	for (int i = 0; i<sz; ++i) cout << " " << A[i];
	cout << endl;
	mergesort(A, 0, sz);
	for (int i = 0; i<sz; ++i) cout << " " << A[i];
	cout << endl;
}


