#include <iostream>
#include <map>
#include <string>
using namespace std;

int main ()
{
	map<int , string> m_str;
	map<string, int>  m_int;

	m_str[0] = "sandeep"; // maps work this way for int keys too!!!
	m_int.insert(make_pair<string,int>("sandeep",0));
}
