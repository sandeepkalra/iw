#include <string>
#include <iostream>
using namespace std;

int main()
{
	string s1{"This is a fully initialized string"};
	s1=move(s1); // moving the string to itself.
	if(s1.empty()) cout<<"The string move to itself leaves it empty!"<<endl;
	
	string s2{"another string"};
	s2=s2; // operator=() to itself
	if(s2.empty()) cout<<"This string is also empty"<<endl;
	else cout<<"operator=() to itself does not leave empty objects"<<endl;
}
