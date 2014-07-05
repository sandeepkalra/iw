#include <iostream>
using namespace std;
#define MAX(a,b) ((a>b)?(a):(b))
int arr[]={400,10,22,34,18,834,14,1902,1123,843};
int sz=0;

void swap(int *a,int l,int r)
{
	//l and r starts from 1 to n, not 0 to n-1.
	int t;
	t = *(a+r);
	*(a+r) = *(a+l);
	*(a+l) = t;
}

void MinHeap(int *a, int end)
{
	int last = end;
	int parent = end/2;
	int left = parent * 2;
	int right = left + 1 ;
	int max = 0;
	
	if(!end) return; /*termination condition for recursion */

	if(right > end) { /* special case, last tree node is only left-child, no right child */
		if(a[parent-1] < a[last-1]) swap(a, parent-1, last-1);
		--last ;
		parent = last /2;		
	}
	
	for( ; parent >= 1; --parent)
	{
		left = parent *2 ;
		right = left + 1;

		max = MAX(a[left-1], a[right-1]);
		if(max > a[parent-1] ) 
		{
			if(max == a[left-1]) swap (a, parent-1, left-1);
			else swap(a, parent-1, right-1);
		}
	}
	
	swap(a, 0, end-1);
	MinHeap(a, end-1);
}

int RemoveMin(int *a, int sz)
{
	int ret = a[0];
	swap(a, 0, sz-1);
	MinHeap(a,sz-1);
	sz--;
	return ret;
}

void AddToHeap(int *a, int sz, int k)
{
	/* assuming a is big enough to hold +1 element */
	a[sz] = k;
	MinHeap(a,sz+1);
}


int main()
{
	sz = 	sizeof(arr)/sizeof(int);
	MinHeap(arr, sz);
	int min = RemoveMin(arr ,sz);
}
