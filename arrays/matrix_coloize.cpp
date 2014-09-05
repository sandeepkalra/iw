#include <iostream>
#include <memory>
#include <algorithm>
#include <array>
using namespace std;

int arr[4][5];

void
colorize (int a[][5], 
	unsigned int x, 
	unsigned int y, 
	int prev_val, 
	int new_val) {
	if(x<4 && y<<5) {
		if(a[x][y] == prev_val) {
			a[x][y] = new_val;
			colorize(a,x,y-1,prev_val,new_val);
			colorize(a,x-1,y-1,prev_val,new_val);
			colorize(a,x+1,y,prev_val,new_val);
			colorize(a,x+1,y+1,prev_val,new_val);
		}
	}
}

int main()
{
	colorize(arr,3,2,0,1);
}
