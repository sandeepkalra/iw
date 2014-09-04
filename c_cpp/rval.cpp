#include <iostream>
#include <string>
using namespace std;

// "const " helps compile the line-below 
void Prn(const string & v) //LValue
{
	cout<<"1 "<<v;
}

void Prn(string&& v) // RValue
{
	cout<<"2 "<<v;
}

int main()
{
	Prn("d");
}
