#include <iostream>
using namespace std;
union s {
	char c;
	int i;
};

int main()
{
	s u;
	u.i=1;
	if(u.c==1) cout<<"little"<<endl;
	else cout<<"big"<<endl;
}
