#include <stdio.h>

void swap(int *a, int l, int r) {
	int t= *(a+l);
	*(a+l)=*(a+r);
	*(a+r)=t;
}

int Partition(int *a, int l, int r) /* r > l */
{
	int pivot_pos = l;
	l++;
	while (l <= r) /*break if left > right */
	{
		if(a[pivot_pos] < a[l]) 
		{ 
			swap(a, l, r); 
			r-- ; 
		}
		else 
		{
			l++;
		}
	}
	swap(a,pivot_pos, l-1);
	return (l-1);
}

void qsort(int *a, int l, int r)
{
	int pivot_pos = 0;
	if(r>l) {
			pivot_pos = Partition(a,l,r);
			qsort(a, l, pivot_pos - 1);
			qsort(a, pivot_pos + 1, r);
	}
}


int arr[]={1,2,3,4,5,6,7,8,9} ;
int main()
{
	int i = 0;
	int sz = (sizeof(arr)/sizeof(int)) -1 ;
	qsort(arr,0, sz);
	for(i=0;i<=sz;++i) printf(" %d", arr[i]);
	getchar();
	return 0;
}
