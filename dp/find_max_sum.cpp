#include <iostream>
/* Find the biggest sum possible in a array of given numbers
* if all numbers are +ve, then , max-sum is all numbers.
* if few numbers are not +ve, then
*  { sum of numbers starting from some value k, 
*   or, this is the start.
*  }
*/

using namespace std;


int main ()
{
	int arr[]={3,4,1,-1,-4,0,12,1,-4};
	int sz_arr = sizeof(arr)/sizeof(int);
	
	int sum = 0;
	int start_pos = 0;
	cout<<"ARRAY: ";
	for (auto i : arr) cout<<" "<<i;
	cout<<endl;
	for(int i = 0; i < sz_arr; ++i) {
		if(sum < arr[i]) { sum = arr[i]; start_pos = i; }
		else if((sum + arr[i]) > sum) sum += arr[i];
	}
	cout<<"Biggest sum is : " << sum <<" Starting @ position "<<start_pos<<endl;;
}
