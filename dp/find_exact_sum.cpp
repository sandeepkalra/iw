// This program only works on array of positive numbers
#include <iostream>
using namespace std;

int main()
{
	int arr[]={1,2,19,83,29,27,7,0,4,8};
	cout<<" ARRAY: ";
	for(auto i: arr) cout<<" "<<i;

	cout<<"\nThis program only works on array of positive numbers ";
	cout<<"\nEnter the exact sum(positive) you are looking for "<<endl;
	int expected_sum = 0;
	cin>>expected_sum;
	int sz_arr = sizeof(arr)/sizeof(int);
	int sum = 0 ;
	int start_pos = 0 ;
	int prev_sum = 0 ;
	for (int i=0;i< sz_arr; ++i) if(arr[i] == expected_sum) { cout<<"found @ location: "<<i<<endl; return 0; }
	
	for(int i = 0; i< sz_arr; ++i) {
		if(expected_sum > (sum + arr[i])) {
			prev_sum  = sum ;
		 	sum += arr[i];
		}
		else if (expected_sum < (sum + arr[i])) {
			prev_sum = sum;
			sum -= arr[start_pos]	;
			start_pos ++;
			i--; // in order to not increment i, we decrement here, and for loop increment it to same value
		} 
		else if(expected_sum == (sum + arr[i] )) {
			cout<<"found near start_pos = "<<start_pos <<endl;
			return 0;
		}
		
	// cout<<"ARR[i]="<<arr[i]<<"i="<<i<<"start-po ="<<start_pos<<",sum="<<sum<<endl;
	}
	cout<<"Not found !"<<endl; 
return 0;
}
