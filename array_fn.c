#include <stdio.h>
#include <stdlib.h>

#define Min(a,b) ((a<b)?(a):(b))
#define Max(b,a) ((a<b)?(a):(b))

//O(n)
signed int find_smallest(signed int *arr, int sz)
{
   signed int smallest = 0x0fffffff;
   int i=0;
   for(i=0;i<sz;++i)
   	{ 
   		if(smallest > arr[i] )
   		 {
   		 	smallest = arr[i]; 
   		 }
   	}
   return smallest;
}

//O(n)
signed int find_largest(signed int *arr, int sz)
{
   signed int largest=-0xffffffff;
	int i=0;
   for(i=0;i<sz;++i) 
   	{ 
   		if(largest < arr[i] ) 
   			{
   				largest = arr[i]; 
   			}
   	}
   return largest;
}

// O(n)
signed int find_missing(signed int *arr, int sz, int start, int end)
{
	int n = end-start+1;
	long expected_sum = n*(n+1)/2; //n(n-1)/2.
	long actual_sum = 0 ;
	int i=0;

	for(i=0;i<sz;++i) actual_sum += arr[i];

	return  (expected_sum - actual_sum);
	
}

//O(log n) -- QUICK SEARCH
int* find_k_largest_numbers(int *array, int sz, int k)
{
	
	int sz_left = 0; int sz_right=0; int i=0;
	int *left = (int*) malloc(sizeof(int)*sz);
    int *right = (int*) malloc(sizeof(int)*sz);
    int *return_ptr = right;
    int pivot=sz/2;

	if(!left || !right) return 0;
    if(k>=sz) return 0;


    for(i=0;i<sz;++i)
	{
        if(array[pivot] < array[i]) right[sz_right++] = array[i]; /* Big pieces move right */
		else   left[sz_left++] = array[i]; /* small pieces move left */
    }
    // There is a flaw in design. IF 'pivot' is biggest number, then all the time, we
    // end up in just one array. This can be prevented by swapping the pivot to some other location.
    if(sz_right==0) {
        int t = left[0];
        left[0]=left[pivot];
        left[pivot]=t;
    }

    if(sz_right==k) /* Right list is what we want */{ free(left); return return_ptr;}
    if(sz_right >k) /*Right has it. infact it has more. */ {free(left); return find_k_largest_numbers(right, sz_right , k);}
    if(sz_right <k) /* Right has few; left has few. Keep the right, pull remaining from left. */
	{
		// we extend right, add the remaining to it from the left.
		// the way we do is, we calculate the few that are in left, and then we join them to right.
		int *p = find_k_largest_numbers(left, sz_left , k - sz_right);
		if(p) {
			for(i=0;i < (k - sz_right); ++i) 
				{ 
					right[sz_right + i] = p[i]; 
				}
			free(left);
            free(p);
		} 

        return return_ptr;
	}	
}

int main()
{
	int i=0;
    signed int array[]={0,-1,1};
	printf("Largest: %d\n", find_largest(array, sizeof(array)/sizeof(signed int)));
	printf("Smallest: %d\n", find_smallest(array, sizeof(array)/sizeof(signed int)));
	 
	int * p = find_k_largest_numbers(array, sizeof(array)/sizeof(int), 3);
    if(p) for(i=0;i<3;++i) printf("  %d \n",p[i]);
    if(p) free(p);
} 
