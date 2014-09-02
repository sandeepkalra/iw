#include <iostream>
/* Find the biggest sum possible in a array of given numbers
* if all numbers are -ve, then , max-sum is all numbers.
* if few numbers are not -ve, then
*  { sum of numbers starting from some value k, 
*   or, this is the start.
*  }
*/

using namespace std;


int main ()
{
	int arr[]={3,4,1,-1,-4,0,12,1,-4,1};
	int sz_arr = sizeof(arr)/sizeof(int);
	
	int sum =0;
	int start_pos = 0;
	int prev = 0;

	cout<<"ARRAY: ";
	for (auto i : arr) cout<<" "<<i;
	cout<<endl;
	for(int i = 0; i < sz_arr; ++i) {
		if ((i-prev) < 2) /* subsequent */
		{
			if ((sum + arr[i]) < sum) {  prev = i; sum += arr[i]; }
			else if(sum > arr[i]) {  start_pos = prev = i ; sum = arr[i];  }
		} 
		else /*Not subsequent */ 	if(sum > arr[i]) { start_pos = prev = i ; sum = arr[i];  }
	}
	cout<<"smallest sum is : " << sum <<" Starting @ position "<<start_pos<<endl;;
}
